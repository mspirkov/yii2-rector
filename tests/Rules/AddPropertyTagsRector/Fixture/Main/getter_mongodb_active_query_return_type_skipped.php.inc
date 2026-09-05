<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\mongodb\ActiveQuery;
use yii\mongodb\ActiveRecord;

class ProductWithMongodbActiveQueryReturningGetter extends ActiveRecord
{
    public function getActiveProducts(): ActiveQuery
    {
        return static::find();
    }
}
