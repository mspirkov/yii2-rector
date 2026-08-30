<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\DynamicMethodNameExample;

class SomeService
{
    public function run(DynamicMethodNameExample $example, string $suffix): string
    {
        return $example->{'get' . $suffix}();
    }
}
