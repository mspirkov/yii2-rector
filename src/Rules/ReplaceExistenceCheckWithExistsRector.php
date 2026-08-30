<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\BinaryOp;
use PhpParser\Node\Expr\BinaryOp\Equal;
use PhpParser\Node\Expr\BinaryOp\Greater;
use PhpParser\Node\Expr\BinaryOp\GreaterOrEqual;
use PhpParser\Node\Expr\BinaryOp\Identical;
use PhpParser\Node\Expr\BinaryOp\NotEqual;
use PhpParser\Node\Expr\BinaryOp\NotIdentical;
use PhpParser\Node\Expr\BinaryOp\Smaller;
use PhpParser\Node\Expr\BinaryOp\SmallerOrEqual;
use PhpParser\Node\Expr\BooleanNot;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Scalar\Int_;
use PHPStan\Type\ObjectType;
use Rector\PhpParser\Node\Value\ValueResolver;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\db\QueryInterface;

final class ReplaceExistenceCheckWithExistsRector extends AbstractRector implements DocumentedRuleInterface
{
    /** @var array<class-string<BinaryOp>, array<int, bool>> */
    private const COUNT_POLARITY_BY_OPERATOR = [
        Greater::class => [0 => true],
        GreaterOrEqual::class => [1 => true],
        NotIdentical::class => [0 => true],
        NotEqual::class => [0 => true],
        Smaller::class => [1 => false],
        SmallerOrEqual::class => [0 => false],
        Identical::class => [0 => false],
        Equal::class => [0 => false],
    ];

    /** @var array<class-string<BinaryOp>, class-string<BinaryOp>> */
    private const FLIPPED_OPERATOR = [
        Greater::class => Smaller::class,
        Smaller::class => Greater::class,
        GreaterOrEqual::class => SmallerOrEqual::class,
        SmallerOrEqual::class => GreaterOrEqual::class,
    ];

    /** @var array<class-string<BinaryOp>, bool> */
    private const ONE_POLARITY_BY_OPERATOR = [
        NotIdentical::class => true,
        Identical::class => false,
    ];

    private ValueResolver $valueResolver;

    public function __construct(ValueResolver $valueResolver)
    {
        $this->valueResolver = $valueResolver;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace an existence check on a `yii\db\QueryInterface` result with the cheaper `->exists()` '
            . 'call. Recognises a `->count()` comparison against the boundary literals `0`/`1` (in either '
            . 'operand order) and a strict `->one() !== null` / `->one() === null` check. A check that '
            . 'means "no rows" (e.g. `count() < 1`, `one() === null`) is rewritten to the negated '
            . '`!exists()`, not `exists()`. Only the boundary comparisons that map unambiguously onto a '
            . 'presence/absence question are recognised — `count() > 1`, for instance, is left untouched',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        public function emailIsTaken(string $email): bool
                        {
                            return User::find()->where(['email' => $email])->one() !== null;
                        }

                        public function emailIsAvailable(string $email): bool
                        {
                            return User::find()->where(['email' => $email])->count() < 1;
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        public function emailIsTaken(string $email): bool
                        {
                            return User::find()->where(['email' => $email])->exists();
                        }

                        public function emailIsAvailable(string $email): bool
                        {
                            return !User::find()->where(['email' => $email])->exists();
                        }
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [BinaryOp::class];
    }

    /**
     * @param BinaryOp $node
     */
    public function refactor(Node $node): ?Node
    {
        $match = $this->matchCountComparison($node) ?? $this->matchOneNullComparison($node);

        if ($match === null) {
            return null;
        }

        [$queryExpr, $exists] = $match;

        if (!$this->isObjectType($queryExpr, new ObjectType(QueryInterface::class))) {
            return null;
        }

        $existsCall = new MethodCall($queryExpr, 'exists');

        return $exists ? $existsCall : new BooleanNot($existsCall);
    }

    /**
     * @return array{0: Expr, 1: bool}|null
     */
    private function matchCountComparison(BinaryOp $node): ?array
    {
        if ($node->left instanceof MethodCall && $this->isName($node->left->name, 'count')) {
            $countCall = $node->left;
            $literal = $node->right;
            $operatorClass = \get_class($node);
        } elseif ($node->right instanceof MethodCall && $this->isName($node->right->name, 'count')) {
            $countCall = $node->right;
            $literal = $node->left;
            $operatorClass = self::FLIPPED_OPERATOR[\get_class($node)] ?? \get_class($node);
        } else {
            return null;
        }

        if (!$literal instanceof Int_) {
            return null;
        }

        $polarity = self::COUNT_POLARITY_BY_OPERATOR[$operatorClass][$literal->value] ?? null;

        if ($polarity === null) {
            return null;
        }

        if ($countCall->getArgs() !== []) {
            return null;
        }

        return [$countCall->var, $polarity];
    }

    /**
     * @return array{0: Expr, 1: bool}|null
     */
    private function matchOneNullComparison(BinaryOp $node): ?array
    {
        $polarity = self::ONE_POLARITY_BY_OPERATOR[\get_class($node)] ?? null;

        if ($polarity === null) {
            return null;
        }

        if ($node->left instanceof MethodCall && $this->isName($node->left->name, 'one')) {
            $oneCall = $node->left;
            $otherSide = $node->right;
        } elseif ($node->right instanceof MethodCall && $this->isName($node->right->name, 'one')) {
            $oneCall = $node->right;
            $otherSide = $node->left;
        } else {
            return null;
        }

        if (!$this->valueResolver->isNull($otherSide)) {
            return null;
        }

        if ($oneCall->getArgs() !== []) {
            return null;
        }

        return [$oneCall->var, $polarity];
    }
}
