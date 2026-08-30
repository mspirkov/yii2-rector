<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\ArrayItem;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\BinaryOp\Concat;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\InterpolatedStringPart;
use PhpParser\Node\Scalar\InterpolatedString;
use PhpParser\Node\Scalar\String_;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

final class ReplaceWhereEqualityConditionWithArrayRector extends AbstractRector implements DocumentedRuleInterface
{
    /** @var list<string> */
    private const WHERE_METHODS = ['where', 'andWhere', 'orWhere'];

    private const COLUMN_PATTERN = '/^(?<column>[a-zA-Z_][a-zA-Z0-9_.]*)\s*=\s*$/';

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace a single-column string `where()`/`andWhere()`/`orWhere()` condition '
            . '(interpolated or concatenated) with the safer array condition format',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        $query->where("column = $value");
                        $query->andWhere('column = ' . $value);
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        $query->where(['column' => $value]);
                        $query->andWhere(['column' => $value]);
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [MethodCall::class];
    }

    /**
     * @param MethodCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (!$this->isNames($node->name, self::WHERE_METHODS)) {
            return null;
        }

        if (\count($node->getArgs()) !== 1) {
            return null;
        }

        $condition = $node->getArgs()[0]->value;

        $columnValuePair = $this->resolveColumnValuePair($condition);

        if ($columnValuePair === null) {
            return null;
        }

        [$column, $value] = $columnValuePair;

        $node->args = [
            $this->nodeFactory->createArg(
                new Array_([new ArrayItem($value, new String_($column))])
            ),
        ];

        return $node;
    }

    /**
     * @return array{0: string, 1: Expr}|null
     */
    private function resolveColumnValuePair(Expr $condition): ?array
    {
        if ($condition instanceof InterpolatedString) {
            return $this->resolveFromInterpolatedString($condition);
        }

        if ($condition instanceof Concat) {
            return $this->resolveFromConcat($condition);
        }

        return null;
    }

    /**
     * @return array{0: string, 1: Expr}|null
     */
    private function resolveFromInterpolatedString(InterpolatedString $interpolatedString): ?array
    {
        if (\count($interpolatedString->parts) !== 2) {
            return null;
        }

        [$stringPart, $valuePart] = $interpolatedString->parts;

        if (!$stringPart instanceof InterpolatedStringPart || !$valuePart instanceof Expr) {
            return null;
        }

        $column = $this->matchColumnName($stringPart->value);

        if ($column === null) {
            return null;
        }

        return [$column, $valuePart];
    }

    /**
     * @return array{0: string, 1: Expr}|null
     */
    private function resolveFromConcat(Concat $concat): ?array
    {
        if (!$concat->left instanceof String_) {
            return null;
        }

        $column = $this->matchColumnName($concat->left->value);

        if ($column === null) {
            return null;
        }

        return [$column, $concat->right];
    }

    private function matchColumnName(string $stringPart): ?string
    {
        if (\preg_match(self::COLUMN_PATTERN, $stringPart, $matches) !== 1) {
            return null;
        }

        return $matches['column'];
    }
}
