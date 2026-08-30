<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\NonGetterMethodNameExample;

class SomeService
{
    public function run(NonGetterMethodNameExample $example): string
    {
        return $example->fetchProp();
    }
}
