<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Identifier;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\BaseYii;

final class ReplaceTraceWithDebugRector extends AbstractRector implements DocumentedRuleInterface
{
    private const TRACE_METHOD = 'trace';

    private const DEBUG_METHOD = 'debug';

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace the deprecated `Yii::trace()` call with `Yii::debug()`',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        Yii::trace('Some message');
                        Yii::trace($data, __METHOD__);
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        Yii::debug('Some message');
                        Yii::debug($data, __METHOD__);
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [StaticCall::class];
    }

    /**
     * @param StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if (!$this->isName($node->name, self::TRACE_METHOD)) {
            return null;
        }

        if (!$this->isObjectType($node->class, new ObjectType(BaseYii::class))) {
            return null;
        }

        $node->name = new Identifier(self::DEBUG_METHOD);

        return $node;
    }
}
