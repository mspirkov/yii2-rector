<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\DynamicModel;

/**
 * @property-read int $legacyCount
 */
class ProductDynamicModel extends DynamicModel
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
