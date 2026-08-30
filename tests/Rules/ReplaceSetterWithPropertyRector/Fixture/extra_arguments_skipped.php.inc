<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\ExtraArgumentsExample;

class SomeService
{
    public function run(ExtraArgumentsExample $example): void
    {
        $example->setProp('value', false);
    }
}
