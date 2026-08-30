<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

class SomeClass extends \yii\base\BaseObject
{
    public static function someOtherMethod(): string
    {
        return 'other';
    }
}

class SomeService
{
    public function run(): string
    {
        return SomeClass::someOtherMethod();
    }
}
