<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterPropertyWriteTagExample;

class SomeService
{
    public function run(SetterPropertyWriteTagExample $example): void
    {
        $example->setProp('value');
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SetterPropertyWriteTagExample;

class SomeService
{
    public function run(SetterPropertyWriteTagExample $example): void
    {
        $example->prop = 'value';
    }
}
