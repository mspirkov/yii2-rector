<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

class SomeClass extends \yii\base\BaseObject
{
    public static function identify(): string
    {
        return static::className();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

class SomeClass extends \yii\base\BaseObject
{
    public static function identify(): string
    {
        return static::class;
    }
}
