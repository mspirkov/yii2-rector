<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $sku
 */
class ProductWithBackedReadTag extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
