<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\NonYiiExample;

class SomeService
{
    public function run(NonYiiExample $example): string
    {
        return $example->getProp();
    }
}
