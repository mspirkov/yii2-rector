<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source\PlainClass;

class SomeService
{
    public function run(): string
    {
        return PlainClass::className();
    }
}
