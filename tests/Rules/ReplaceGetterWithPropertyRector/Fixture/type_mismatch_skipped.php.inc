<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\TypeMismatchExample;

class SomeService
{
    public function run(TypeMismatchExample $example): int
    {
        return $example->getProp();
    }
}
