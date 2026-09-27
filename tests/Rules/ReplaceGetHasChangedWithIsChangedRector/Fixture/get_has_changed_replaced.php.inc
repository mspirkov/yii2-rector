<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Fixture;

use yii\caching\CacheInterface;
use yii\caching\Dependency;

class SomeService
{
    public function hasChanged(Dependency $dependency, CacheInterface $cache): bool
    {
        return $dependency->getHasChanged($cache);
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Fixture;

use yii\caching\CacheInterface;
use yii\caching\Dependency;

class SomeService
{
    public function hasChanged(Dependency $dependency, CacheInterface $cache): bool
    {
        return $dependency->isChanged($cache);
    }
}
