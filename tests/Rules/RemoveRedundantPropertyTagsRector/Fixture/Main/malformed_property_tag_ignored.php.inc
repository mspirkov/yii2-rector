<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read
 */
class ProductWithMalformedTag extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
