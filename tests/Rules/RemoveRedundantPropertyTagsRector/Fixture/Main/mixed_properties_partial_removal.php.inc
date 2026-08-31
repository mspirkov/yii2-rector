<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $sku
 * @property-read int $legacyCount
 * @property-write float $discount
 */
class ProductWithMixedTags extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }

    public function setDiscount(float $discount): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $sku
 * @property-write float $discount
 */
class ProductWithMixedTags extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }

    public function setDiscount(float $discount): void
    {
    }
}
