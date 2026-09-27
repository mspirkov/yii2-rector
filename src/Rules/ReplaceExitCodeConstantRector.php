<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\ClassConstFetch;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\console\Controller;
use yii\console\ExitCode;

final class ReplaceExitCodeConstantRector extends AbstractRector implements DocumentedRuleInterface
{
    /** @var array<string, string> */
    private const CONSTANT_MAP = [
        'EXIT_CODE_NORMAL' => 'OK',
        'EXIT_CODE_ERROR' => 'UNSPECIFIED_ERROR',
    ];

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace a console controller\'s deprecated `Controller::EXIT_CODE_NORMAL`/`EXIT_CODE_ERROR` '
                . 'constant with the `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` equivalent',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class ProcessController extends Controller
                        {
                            public function actionRun()
                            {
                                return self::EXIT_CODE_NORMAL;
                            }
                        }
                        CODE_SAMPLE,
                    <<<'CODE_SAMPLE'
                        class ProcessController extends Controller
                        {
                            public function actionRun()
                            {
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
        return [ClassConstFetch::class];
    }

    /**
     * @param ClassConstFetch $node
     */
    public function refactor(Node $node): ?Node
    {
        $constantName = $this->getName($node->name);

        if ($constantName === null || !isset(self::CONSTANT_MAP[$constantName])) {
            return null;
        }

        if (!$this->isObjectType($node->class, new ObjectType(Controller::class))) {
            return null;
        }

        return $this->nodeFactory->createClassConstFetch(
            ExitCode::class,
            self::CONSTANT_MAP[$constantName]
        );
    }
}
