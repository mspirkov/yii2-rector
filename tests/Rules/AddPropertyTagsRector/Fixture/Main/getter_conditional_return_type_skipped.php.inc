<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithConditionalReturnType extends BaseObject
{
    /**
     * @param bool $asString
     *
     * @return ($asString is true ? string : int)
     */
    public function getPrice(bool $asString = false)
    {
        return $asString ? '9.99' : 999;
    }
}
