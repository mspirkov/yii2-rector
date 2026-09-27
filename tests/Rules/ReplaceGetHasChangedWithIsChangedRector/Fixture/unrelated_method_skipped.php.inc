<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Fixture;

use yii\caching\CacheInterface;
use yii\caching\Dependency;

class SomeService
{
    public function evaluate(Dependency $dependency, CacheInterface $cache): void
    {
        $dependency->evaluateDependency($cache);
    }
}
