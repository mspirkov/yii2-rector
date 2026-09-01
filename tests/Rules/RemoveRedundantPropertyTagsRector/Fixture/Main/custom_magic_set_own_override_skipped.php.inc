<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property string $legacyName
 */
class ProductWithCustomMagicSet extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }

    /**
     * @param mixed $name
     * @param mixed $value
     */
    public function __set($name, $value)
    {
    }
}
