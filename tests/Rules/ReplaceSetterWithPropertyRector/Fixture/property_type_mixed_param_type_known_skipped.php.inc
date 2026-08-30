<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\PropertyTypeMixedSetterExample;

class SomeService
{
    public function run(PropertyTypeMixedSetterExample $example): void
    {
        $example->setProp('value');
    }
}
