<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source\SomeClass;

class SomeService
{
    public function run(): string
    {
        $class = SomeClass::class;

        return $class::className();
    }
}
