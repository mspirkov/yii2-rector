<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterTypeMismatchExample;

class SomeService
{
    public function run(SetterTypeMismatchExample $example): void
    {
        $example->setProp('5');
    }
}
