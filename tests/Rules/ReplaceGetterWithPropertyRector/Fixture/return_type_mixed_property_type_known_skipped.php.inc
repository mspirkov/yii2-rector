<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\ReturnTypeMixedExample;

class SomeService
{
    /**
     * @return mixed
     */
    public function run(ReturnTypeMixedExample $example)
    {
        return $example->getProp();
    }
}
