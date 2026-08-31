<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source\SomeClass;

class SomeService
{
    public function run(): string
    {
        return SomeClass::className();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source\SomeClass;

class SomeService
{
    public function run(): string
    {
        return SomeClass::class;
    }
}
