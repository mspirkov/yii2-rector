<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\UnionFirstExample;
use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\UnionSecondExample;

class SomeService
{
    /**
     * @param UnionFirstExample|UnionSecondExample $example
     */
    public function run($example): string
    {
        return $example->getProp();
    }
}
