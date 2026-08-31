<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

/**
 * @property-read int $legacyCount
 */
class ProductNotExtendingBaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
