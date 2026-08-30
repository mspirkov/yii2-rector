<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\NativeSetterPropertyExample;

class SomeService
{
    public function run(NativeSetterPropertyExample $example): void
    {
        $example->setProp(5);
    }
}
