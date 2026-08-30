<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyTagReadWriteExample;

class SomeService
{
    public function run(PropertyTagReadWriteExample $example): string
    {
        return $example->getProp();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\PropertyTagReadWriteExample;

class SomeService
{
    public function run(PropertyTagReadWriteExample $example): string
    {
        return $example->prop;
    }
}
