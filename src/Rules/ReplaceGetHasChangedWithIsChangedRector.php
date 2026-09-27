<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Identifier;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\caching\Dependency;

final class ReplaceGetHasChangedWithIsChangedRector extends AbstractRector implements DocumentedRuleInterface
{
    private const GET_HAS_CHANGED_METHOD = 'getHasChanged';

    private const IS_CHANGED_METHOD = 'isChanged';

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace the deprecated `yii\caching\Dependency::getHasChanged()` call with `isChanged()`',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        $hasChanged = $dependency->getHasChanged($cache);
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        $hasChanged = $dependency->isChanged($cache);
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
        if (!$this->isName($node->name, self::GET_HAS_CHANGED_METHOD)) {
            return null;
        }

        if (!$this->isObjectType($node->var, new ObjectType(Dependency::class))) {
            return null;
        }

        $node->name = new Identifier(self::IS_CHANGED_METHOD);

        return $node;
    }
}
