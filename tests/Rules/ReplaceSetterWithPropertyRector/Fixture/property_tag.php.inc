<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterPropertyTagReadWriteExample;

class SomeService
{
    public function run(SetterPropertyTagReadWriteExample $example): void
    {
        $example->setProp('value');
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterPropertyTagReadWriteExample;

class SomeService
{
    public function run(SetterPropertyTagReadWriteExample $example): void
    {
        $example->prop = 'value';
    }
}
