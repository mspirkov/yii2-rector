<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\redis\ActiveQuery;
use yii\redis\ActiveRecord;

class ProductWithRedisActiveQueryReturningGetter extends ActiveRecord
{
    public function getActiveProducts(): ActiveQuery
    {
        return static::find();
    }
}
