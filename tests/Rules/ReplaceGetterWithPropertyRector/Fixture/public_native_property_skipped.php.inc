<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PublicNativePropertyExample;

class SomeService
{
    public function run(PublicNativePropertyExample $example): string
    {
        return $example->getProp();
    }
}
