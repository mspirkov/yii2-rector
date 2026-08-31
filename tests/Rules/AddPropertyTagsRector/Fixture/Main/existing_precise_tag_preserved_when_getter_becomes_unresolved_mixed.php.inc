<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $data
 */
class ProductWithUntypedGetterAndPreciseExistingReadTag extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }
}
