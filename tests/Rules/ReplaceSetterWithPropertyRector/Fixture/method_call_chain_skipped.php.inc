<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\FluentSetterExample;

class SomeService
{
    public function run(FluentSetterExample $example): void
    {
        $example->setProp('value')->setOtherProp('other');
    }
}
