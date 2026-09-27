<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceCacheMultiMethodAliasesRector\Fixture;

use yii\caching\Cache;

class SomeService
{
    public function run(Cache $cache): array
    {
        return $cache->madd(['key3' => 'value3']);
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
        return $cache->multiAdd(['key3' => 'value3']);
    }
}
