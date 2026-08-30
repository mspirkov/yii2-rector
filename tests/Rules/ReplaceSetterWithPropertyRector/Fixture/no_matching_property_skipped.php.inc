<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\NoMatchingSetterPropertyExample;

class SomeService
{
    public function run(NoMatchingSetterPropertyExample $example): void
    {
        $example->setFullName('Jane Roe');
    }
}
