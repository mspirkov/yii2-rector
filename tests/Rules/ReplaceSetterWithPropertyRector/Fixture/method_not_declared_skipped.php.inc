<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterMethodNotDeclaredExample;

class SomeService
{
    public function run(SetterMethodNotDeclaredExample $example): void
    {
        $example->setProp('value');
    }
}
