<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Source;

class NonCacheObject
{
    /**
     * @param string[] $keys
     *
     * @return mixed[]
     */
    public function mget(array $keys): array
    {
        return [];
    }
}
