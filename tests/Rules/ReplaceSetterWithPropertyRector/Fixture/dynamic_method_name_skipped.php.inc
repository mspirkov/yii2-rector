<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\DynamicSetterMethodNameExample;

class SomeService
{
    public function run(DynamicSetterMethodNameExample $example, string $suffix, string $value): void
    {
        $example->{'set' . $suffix}($value);
    }
}
