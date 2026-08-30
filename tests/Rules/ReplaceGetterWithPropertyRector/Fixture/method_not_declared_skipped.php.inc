<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\GetterMethodNotDeclaredExample;

class SomeService
{
    public function run(GetterMethodNotDeclaredExample $example): string
    {
        return $example->getProp();
    }
}
