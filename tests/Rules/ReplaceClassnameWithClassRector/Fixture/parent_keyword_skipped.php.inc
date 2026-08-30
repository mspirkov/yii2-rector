<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source\ParentClass;

class ChildClass extends ParentClass
{
    public static function identify(): string
    {
        return parent::className();
    }
}
