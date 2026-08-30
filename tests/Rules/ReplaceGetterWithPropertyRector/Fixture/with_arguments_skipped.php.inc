<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\WithArgumentsExample;

class SomeService
{
    public function run(WithArgumentsExample $example): string
    {
        return $example->getProp('fallback');
    }
}
