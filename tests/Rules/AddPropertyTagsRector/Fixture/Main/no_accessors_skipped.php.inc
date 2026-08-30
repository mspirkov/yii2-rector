<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithNoAccessors extends BaseObject
{
    public string $sku = '';

    public function formatForDisplay(): string
    {
        return $this->sku;
    }
}
