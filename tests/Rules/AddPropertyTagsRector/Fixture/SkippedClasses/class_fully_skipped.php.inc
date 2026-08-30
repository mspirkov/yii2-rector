<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read string $sku custom description.
 */
class SkippedProduct extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
