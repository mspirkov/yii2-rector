<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\NoParameterSetterExample;

class SomeService
{
    public function run(NoParameterSetterExample $example): void
    {
        $example->setProp('value');
    }
}
