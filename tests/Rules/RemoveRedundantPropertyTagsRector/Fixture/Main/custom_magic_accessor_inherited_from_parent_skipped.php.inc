<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Source\CustomMagicAccessorBase;

/**
 * @property string $legacyName
 */
class ProductWithInheritedCustomMagicGet extends CustomMagicAccessorBase
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
