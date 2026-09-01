<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductActiveRecordWithCustomMagicGet extends ActiveRecord
{
    public function getSku(): string
    {
        return 'SKU-1';
    }

    /**
     * @param mixed $name
     * @return mixed
     */
    public function __get($name)
    {
        return parent::__get($name);
    }
}
