<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use yii\caching\Cache;

class SomeService
{
    public function run(Cache $cache): array
    {
        return $cache->mset(['key1' => 'value1', 'key2' => 'value2']);
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use yii\caching\Cache;

class SomeService
{
    public function run(Cache $cache): array
    {
        return $cache->multiSet(['key1' => 'value1', 'key2' => 'value2']);
    }
}
