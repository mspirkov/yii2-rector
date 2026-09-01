<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property string $legacyName
 */
class ProductWithCustomMagicGet extends BaseObject
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
        return null;
    }
}
