<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property int $legacy_column
 */
class ProductActiveRecord extends ActiveRecord
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
