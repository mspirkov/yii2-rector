<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithProtectedGetter extends BaseObject
{
    protected function getInternalToken(): string
    {
        return 'token';
    }
}
