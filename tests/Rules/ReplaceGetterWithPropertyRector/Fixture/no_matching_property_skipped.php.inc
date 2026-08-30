<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\NoMatchingPropertyExample;

class SomeService
{
    public function run(NoMatchingPropertyExample $example): string
    {
        return $example->getFullName();
    }
}
