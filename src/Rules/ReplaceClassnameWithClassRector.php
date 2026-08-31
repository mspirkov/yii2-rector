<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\StaticCall;
use PhpParser\Node\Name;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\base\BaseObject;

final class ReplaceClassnameWithClassRector extends AbstractRector implements DocumentedRuleInterface
{
    private const CLASSNAME_METHOD = 'className';

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace the deprecated `yii\base\BaseObject::className()` call with the native `::class` constant. '
            . '`self::className()` and `parent::className()` are left untouched, since both are '
            . 'late-static-binding forwarding calls not generally equivalent to `self::class`/`parent::class` '
            . 'once the class is subclassed — only `static::className()` and an explicit class name are '
            . 'rewritten',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        $class = SomeClass::className();
                        $class = static::className();
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        $class = SomeClass::class;
                        $class = static::class;
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
        if (!$node->class instanceof Name) {
            return null;
        }

        // "self::className()" and "parent::className()" forward the caller's late static
        // binding, so they are not equivalent to the compile-time "self::class"/"parent::class".
        if ($this->isNames($node->class, ['self', 'parent'])) {
            return null;
        }

        if ($node->getArgs() !== []) {
            return null;
        }

        if (!$this->isName($node->name, self::CLASSNAME_METHOD)) {
            return null;
        }

        if (!$this->isObjectType($node->class, new ObjectType(BaseObject::class))) {
            return null;
        }

        return $this->nodeFactory->createClassConstFetchFromName(clone $node->class, 'class');
    }
}
