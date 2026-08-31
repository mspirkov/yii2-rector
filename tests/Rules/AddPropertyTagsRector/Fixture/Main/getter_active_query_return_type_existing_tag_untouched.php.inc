<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveQuery;
use yii\db\ActiveRecord;

/**
 * @property-read ActiveQuery $activeProducts
 */
class ProductWithActiveQueryGetterAndStaleTag extends ActiveRecord
{
    public function getActiveProducts(): ActiveQuery
    {
        return static::find();
    }
}
