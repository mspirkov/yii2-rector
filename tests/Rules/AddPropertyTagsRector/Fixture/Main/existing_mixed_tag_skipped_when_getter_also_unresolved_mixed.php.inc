<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read mixed $data
 */
class ProductWithUntypedGetterAndExistingMixedTag extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }
}
