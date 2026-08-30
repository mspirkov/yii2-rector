<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\NativePropertyExample;

class SomeService
{
    public function run(NativePropertyExample $example): ?int
    {
        return $example->getProp();
    }
}
