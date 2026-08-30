<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithRequiredSecondSetterParam extends BaseObject
{
    public function setPrice(float $price, string $currency): void
    {
    }
}
