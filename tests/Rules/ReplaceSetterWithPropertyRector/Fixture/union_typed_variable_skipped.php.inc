<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\UnionFirstSetterExample;
use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\UnionSecondSetterExample;

class SomeService
{
    /**
     * @param UnionFirstSetterExample|UnionSecondSetterExample $example
     */
    public function run($example): void
    {
        $example->setProp('value');
    }
}
