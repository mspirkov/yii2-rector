<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithPrivateGetter extends BaseObject
{
    private function getInternalToken(): string
    {
        return 'token';
    }
}
