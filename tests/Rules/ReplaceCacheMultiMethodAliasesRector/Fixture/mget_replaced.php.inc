<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use yii\caching\Cache;

class SomeService
{
    public function run(Cache $cache): array
    {
        return $cache->mget(['key1', 'key2']);
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
        return $cache->multiGet(['key1', 'key2']);
    }
}
