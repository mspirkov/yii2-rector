<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithStaticGetter extends BaseObject
{
    public static function getDefaultCurrency(): string
    {
        return 'USD';
    }
}
