<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\MixedSetterTypeExample;

class SomeService
{
    public function run(MixedSetterTypeExample $example): void
    {
        $example->setProp('value');
    }
}
