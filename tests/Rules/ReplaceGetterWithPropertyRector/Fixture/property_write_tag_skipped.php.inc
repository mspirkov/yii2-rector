<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyWriteTagExample;

class SomeService
{
    public function run(PropertyWriteTagExample $example): string
    {
        return $example->getProp();
    }
}
