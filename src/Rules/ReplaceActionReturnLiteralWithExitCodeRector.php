<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Scalar\Int_;
use PhpParser\Node\Stmt\ClassMethod;
use PHPStan\Analyser\Scope;
use PHPStan\Reflection\ClassReflection;
use Rector\NodeTypeResolver\Node\AttributeKey;
use Rector\PhpParser\Node\BetterNodeFinder;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\console\Controller;
use yii\console\ExitCode;

final class ReplaceActionReturnLiteralWithExitCodeRector extends AbstractRector implements DocumentedRuleInterface
{
    private const ACTION_METHOD_NAME_PATTERN = '/^action[A-Z]\w*$/';

    /** @var array<int, string> */
    private const LITERAL_MAP = [
        0 => 'OK',
        1 => 'UNSPECIFIED_ERROR',
    ];

    private BetterNodeFinder $betterNodeFinder;

    public function __construct(BetterNodeFinder $betterNodeFinder)
    {
        $this->betterNodeFinder = $betterNodeFinder;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace a literal `return 0;`/`return 1;` in one of a console controller\'s `action*()` '
            . 'methods with the equivalent `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` constant. A return '
            . 'inside a closure/arrow function nested in the action method is left untouched, since it '
            . "isn't the action's own exit code",
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class ProcessController extends Controller
                        {
                            public function actionRun(bool $allowed)
                            {
                                if (!$allowed) {
                                    return 1;
                                }

                                return 0;
                            }
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        class ProcessController extends Controller
                        {
                            public function actionRun(bool $allowed)
                            {
                                if (!$allowed) {
                                    return ExitCode::UNSPECIFIED_ERROR;
                                }

                                return ExitCode::OK;
                            }
                        }
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [ClassMethod::class];
    }

    /**
     * @param ClassMethod $node
     */
    public function refactor(Node $node): ?Node
    {
        if ($node->isStatic() || !$node->isPublic()) {
            return null;
        }

        $methodName = $this->getName($node);

        if (\preg_match(self::ACTION_METHOD_NAME_PATTERN, $methodName) !== 1) {
            return null;
        }

        if (!$this->isInsideConsoleController($node)) {
            return null;
        }

        $hasChanged = false;

        foreach ($this->betterNodeFinder->findReturnsScoped($node) as $return) {
            $exitCodeConstFetch = $this->resolveLiteralExitCode($return->expr);

            if ($exitCodeConstFetch === null) {
                continue;
            }

            $return->expr = $exitCodeConstFetch;
            $hasChanged = true;
        }

        return $hasChanged ? $node : null;
    }

    private function isInsideConsoleController(ClassMethod $classMethod): bool
    {
        $scope = $classMethod->getAttribute(AttributeKey::SCOPE);

        if (!$scope instanceof Scope) {
            return false;
        }

        $classReflection = $scope->getClassReflection();

        return $classReflection instanceof ClassReflection && $classReflection->is(Controller::class);
    }

    private function resolveLiteralExitCode(?Expr $returnExpr): ?ClassConstFetch
    {
        if (!$returnExpr instanceof Int_ || !isset(self::LITERAL_MAP[$returnExpr->value])) {
            return null;
        }

        return $this->nodeFactory->createClassConstFetch(ExitCode::class, self::LITERAL_MAP[$returnExpr->value]);
    }
}
