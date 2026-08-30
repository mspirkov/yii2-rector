<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\NonSetterMethodNameExample;

class SomeService
{
    public function run(NonSetterMethodNameExample $example): void
    {
        $example->updateProp('value');
    }
}
