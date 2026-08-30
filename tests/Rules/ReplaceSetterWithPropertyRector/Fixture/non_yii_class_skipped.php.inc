<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\NonYiiSetterExample;

class SomeService
{
    public function run(NonYiiSetterExample $example): void
    {
        $example->setProp('value');
    }
}
