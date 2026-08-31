<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\ProductQuery;
use yii\db\ActiveRecord;

class ProductWithActiveQuerySubclassReturningGetter extends ActiveRecord
{
    public function getActiveProducts(): ProductQuery
    {
        return new ProductQuery(static::class);
    }
}
