<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyTypeMixedExample;

class SomeService
{
    public function run(PropertyTypeMixedExample $example): string
    {
        return $example->getProp();
    }
}
