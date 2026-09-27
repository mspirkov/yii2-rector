<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use yii\caching\Cache;

class SomeService
{
    public function run(Cache $cache)
    {
        return $cache->get('key1');
    }
}
