<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write string $sku
 */
class ProductWithBackedWriteTag extends BaseObject
{
    public function setSku(string $sku): void
    {
    }
}
