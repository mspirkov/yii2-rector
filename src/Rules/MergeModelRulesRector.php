<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\ArrayItem;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Return_;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\base\Model;

final class MergeModelRulesRector extends AbstractRector implements DocumentedRuleInterface
{
    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Merge `yii\base\Model::rules()` entries that configure the same validator with the same '
            . 'options but a different attribute into one entry, combining their attributes into a '
            . 'single array (an attribute already present in another merged entry is not duplicated). '
            . 'Two entries only merge when everything after the attribute(s) — the validator and any '
            . 'options — is identical; a `rules()` body that isn\'t a single `return [...]` of literal '
            . 'rule arrays is left untouched',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class LoginForm extends Model
                        {
                            public function rules(): array
                            {
                                return [
                                    ['login', 'required'],
                                    ['password', 'required'],
                                ];
                            }
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        class LoginForm extends Model
                        {
                            public function rules(): array
                            {
                                return [
                                    [['login', 'password'], 'required'],
                                ];
                            }
                        }
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if ($node->isAnonymous()) {
            return null;
        }

        if (!$this->isObjectType($node, new ObjectType(Model::class))) {
            return null;
        }

        $rulesMethod = $node->getMethod('rules');

        if ($rulesMethod === null) {
            return null;
        }

        $topArray = $this->matchTopLevelArray($rulesMethod);

        if ($topArray === null) {
            return null;
        }

        $tuples = $this->resolveTuples($topArray);
        $groups = $this->groupMergeableIndices($tuples);

        if ($groups === []) {
            return null;
        }

        $this->mergeGroups($topArray, $tuples, $groups);

        return $node;
    }

    private function matchTopLevelArray(ClassMethod $classMethod): ?Array_
    {
        $stmts = $classMethod->stmts;

        if ($stmts === null || \count($stmts) !== 1) {
            return null;
        }

        $onlyStmt = $stmts[0];

        if (!$onlyStmt instanceof Return_ || $onlyStmt->expr === null) {
            return null;
        }

        if (!$onlyStmt->expr instanceof Array_) {
            return null;
        }

        return $onlyStmt->expr;
    }

    /**
     * @return list<array{index: int, attrExprs: list<Expr>, restItems: list<ArrayItem>, tupleArray: Array_}>
     */
    private function resolveTuples(Array_ $topArray): array
    {
        $tuples = [];

        foreach ($topArray->items as $index => $topItem) {
            $tuple = $this->parseTuple($topItem);

            if ($tuple !== null) {
                $tuples[] = [
                    'index' => (int) $index,
                    'attrExprs' => $tuple['attrExprs'],
                    'restItems' => $tuple['restItems'],
                    'tupleArray' => $tuple['tupleArray'],
                ];
            }
        }

        return $tuples;
    }

    /**
     * @return array{attrExprs: list<Expr>, restItems: list<ArrayItem>, tupleArray: Array_}|null
     */
    private function parseTuple(ArrayItem $topItem): ?array
    {
        if ($topItem->byRef || $topItem->unpack || $topItem->key !== null) {
            return null;
        }

        if (!$topItem->value instanceof Array_) {
            return null;
        }

        $tupleArray = $topItem->value;

        if (\count($tupleArray->items) < 2) {
            return null;
        }

        $attributeItem = $tupleArray->items[0];

        if ($attributeItem->byRef || $attributeItem->unpack || $attributeItem->key !== null) {
            return null;
        }

        $attrExprs = $this->resolveAttributeExprs($attributeItem->value);

        if ($attrExprs === []) {
            return null;
        }

        $restItems = [];

        foreach ($tupleArray->items as $itemIndex => $tupleItem) {
            if ($itemIndex !== 0) {
                $restItems[] = $tupleItem;
            }
        }

        return [
            'attrExprs' => $attrExprs,
            'restItems' => $restItems,
            'tupleArray' => $tupleArray,
        ];
    }

    /**
     * @return list<Expr>
     */
    private function resolveAttributeExprs(Expr $expr): array
    {
        if (!$expr instanceof Array_) {
            return [$expr];
        }

        $exprs = [];

        foreach ($expr->items as $item) {
            if ($item->byRef || $item->unpack || $item->key !== null) {
                return [];
            }

            $exprs[] = $item->value;
        }

        return $exprs;
    }

    /**
     * @param list<array{index: int, attrExprs: list<Expr>, restItems: list<ArrayItem>, tupleArray: Array_}> $tuples
     *
     * @return list<list<int>>
     */
    private function groupMergeableIndices(array $tuples): array
    {
        $indicesByKey = [];

        foreach ($tuples as $tuple) {
            $key = $this->nodeComparator->printWithoutComments($tuple['restItems']);
            $indicesByKey[$key][] = $tuple['index'];
        }

        $groups = [];

        foreach ($indicesByKey as $indices) {
            if (\count($indices) >= 2) {
                $groups[] = $indices;
            }
        }

        return $groups;
    }

    /**
     * @param list<array{index: int, attrExprs: list<Expr>, restItems: list<ArrayItem>, tupleArray: Array_}> $tuples
     * @param list<list<int>> $groups
     */
    private function mergeGroups(Array_ $topArray, array $tuples, array $groups): void
    {
        $tuplesByIndex = [];

        foreach ($tuples as $tuple) {
            $tuplesByIndex[$tuple['index']] = $tuple;
        }

        $indicesToRemove = [];

        foreach ($groups as $indices) {
            $firstIndex = $indices[0];
            $mergedAttrExprs = [];

            foreach ($indices as $index) {
                foreach ($tuplesByIndex[$index]['attrExprs'] as $attrExpr) {
                    if (!$this->containsEqualExpr($mergedAttrExprs, $attrExpr)) {
                        $mergedAttrExprs[] = $attrExpr;
                    }
                }
            }

            $newAttributeExpr = \count($mergedAttrExprs) === 1
                ? $mergedAttrExprs[0]
                : new Array_($this->createArrayItems($mergedAttrExprs));

            $tuplesByIndex[$firstIndex]['tupleArray']->items[0] = new ArrayItem($newAttributeExpr);

            foreach (\array_slice($indices, 1) as $index) {
                $indicesToRemove[$index] = true;
            }
        }

        $newTopItems = [];

        foreach ($topArray->items as $index => $topItem) {
            if (!isset($indicesToRemove[$index])) {
                $newTopItems[] = $topItem;
            }
        }

        $topArray->items = $newTopItems;
    }

    /**
     * @param list<Expr> $exprs
     */
    private function containsEqualExpr(array $exprs, Expr $expr): bool
    {
        foreach ($exprs as $existingExpr) {
            if ($this->nodeComparator->areNodesEqual($existingExpr, $expr)) {
                return true;
            }
        }

        return false;
    }

    /**
     * @param list<Expr> $exprs
     *
     * @return list<ArrayItem>
     */
    private function createArrayItems(array $exprs): array
    {
        $items = [];

        foreach ($exprs as $expr) {
            $items[] = new ArrayItem($expr);
        }

        return $items;
    }
}
