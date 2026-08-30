<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Scalar\String_;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\db\ActiveRecordInterface;

final class ReplaceFindWhereOneWithFindOneRector extends AbstractRector implements DocumentedRuleInterface
{
    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace `find()->where([...])->one()` on an ActiveRecord class with the equivalent '
            . '`findOne([...])`. Only fires when the `where()` condition is a literal array keyed '
            . 'entirely by string literals: `findOne()` treats any other condition shape (scalar, '
            . 'list, `Expression`) as a primary key lookup instead of forwarding it to `where()` '
            . 'unchanged, so those shapes are intentionally left untouched.',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        $customer = Customer::find()->where(['status' => 1])->one();
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        $customer = Customer::findOne(['status' => 1]);
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
        if (!$this->isName($node->name, 'one')) {
            return null;
        }

        if ($node->getArgs() !== []) {
            return null;
        }

        $whereCall = $node->var;

        if (!$whereCall instanceof MethodCall) {
            return null;
        }

        if (!$this->isName($whereCall->name, 'where')) {
            return null;
        }

        if (\count($whereCall->getArgs()) !== 1) {
            return null;
        }

        $condition = $whereCall->getArgs()[0]->value;

        if (!$condition instanceof Array_ || !$this->isAssociativeArrayLiteral($condition)) {
            return null;
        }

        $findCall = $whereCall->var;

        if (!$findCall instanceof StaticCall) {
            return null;
        }

        if (!$this->isName($findCall->name, 'find')) {
            return null;
        }

        if ($findCall->getArgs() !== []) {
            return null;
        }

        if (!$this->isObjectType($findCall->class, new ObjectType(ActiveRecordInterface::class))) {
            return null;
        }

        return new StaticCall($findCall->class, 'findOne', $whereCall->getArgs());
    }

    private function isAssociativeArrayLiteral(Array_ $array): bool
    {
        if ($array->items === []) {
            return false;
        }

        foreach ($array->items as $item) {
            if (!$item->key instanceof String_) {
                return false;
            }
        }

        return true;
    }
}
