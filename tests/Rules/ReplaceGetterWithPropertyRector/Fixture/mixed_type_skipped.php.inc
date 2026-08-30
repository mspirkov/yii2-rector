<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\MixedTypeExample;

class SomeService
{
    /**
     * @return mixed
     */
    public function run(MixedTypeExample $example)
    {
        return $example->getProp();
    }
}
