<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithParameterizedGetter extends BaseObject
{
    public function getFormattedPrice(string $format): string
    {
        return $format;
    }
}
