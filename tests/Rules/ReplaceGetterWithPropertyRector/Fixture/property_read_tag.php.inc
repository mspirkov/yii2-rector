<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyTagExample;

class SomeService
{
    public function run(PropertyTagExample $example): string
    {
        return $example->getProp();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyTagExample;

class SomeService
{
    public function run(PropertyTagExample $example): string
    {
        return $example->prop;
    }
}
