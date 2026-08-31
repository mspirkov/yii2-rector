<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 * @property-read float $legacyWeight
 */
class PartiallySkippedProduct extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 */
class PartiallySkippedProduct extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
