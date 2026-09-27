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
use yii\caching\Cache;

final class ReplaceCacheMultiMethodAliasesRector extends AbstractRector implements DocumentedRuleInterface
{
    /** @var array<string, string> */
    private const METHOD_MAP = [
        'mget' => 'multiGet',
        'mset' => 'multiSet',
        'madd' => 'multiAdd',
    ];

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace a deprecated `yii\caching\Cache` multi-key method alias — `mget()`, `mset()`, or '
            . '`madd()` — with its canonical `multiGet()`, `multiSet()`, or `multiAdd()` equivalent',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        $cache->mget(['key1', 'key2']);
                        $cache->mset(['key1' => 'value1', 'key2' => 'value2']);
                        $cache->madd(['key3' => 'value3']);
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        $cache->multiGet(['key1', 'key2']);
                        $cache->multiSet(['key1' => 'value1', 'key2' => 'value2']);
                        $cache->multiAdd(['key3' => 'value3']);
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
        $methodName = $this->getName($node->name);

        if ($methodName === null || !isset(self::METHOD_MAP[$methodName])) {
            return null;
        }

        if (!$this->isObjectType($node->var, new ObjectType(Cache::class))) {
            return null;
        }

        $node->name = new Identifier(self::METHOD_MAP[$methodName]);

        return $node;
    }
}
