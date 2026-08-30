<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithConditionalParamType extends BaseObject
{
    /**
     * @param ($strict is true ? int : int|string) $value
     * @param bool $strict
     */
    public function setValue($value, bool $strict = false): void
    {
    }
}
