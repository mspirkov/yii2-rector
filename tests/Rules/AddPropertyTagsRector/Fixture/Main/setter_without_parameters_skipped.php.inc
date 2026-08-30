<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithParameterlessSetter extends BaseObject
{
    private array $_defaults = [];

    public function setDefaults(): void
    {
        $this->_defaults = [];
    }
}
