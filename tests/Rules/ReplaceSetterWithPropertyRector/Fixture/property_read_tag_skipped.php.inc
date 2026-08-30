<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\PropertyReadTagExample;

class SomeService
{
    public function run(PropertyReadTagExample $example): void
    {
        $example->setProp('value');
    }
}
