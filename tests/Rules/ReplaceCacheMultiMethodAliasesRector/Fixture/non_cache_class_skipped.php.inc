<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Source\NonCacheObject;

class SomeService
{
    public function run(NonCacheObject $object): array
    {
        return $object->mget(['key1', 'key2']);
    }
}
