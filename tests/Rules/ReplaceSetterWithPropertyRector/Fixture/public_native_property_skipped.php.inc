<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\PublicNativeSetterPropertyExample;

class SomeService
{
    public function run(PublicNativeSetterPropertyExample $example): void
    {
        $example->setProp('value');
    }
}
