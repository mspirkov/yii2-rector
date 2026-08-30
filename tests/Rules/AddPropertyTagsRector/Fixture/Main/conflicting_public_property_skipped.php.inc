<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithNativePublicProperty extends BaseObject
{
    public string $name = '';

    public function getName(): string
    {
        return $this->name;
    }
}
