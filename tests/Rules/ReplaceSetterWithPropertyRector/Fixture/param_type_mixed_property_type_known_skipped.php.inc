<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\ParamTypeMixedExample;

class SomeService
{
    public function run(ParamTypeMixedExample $example): void
    {
        $example->setProp('value');
    }
}
