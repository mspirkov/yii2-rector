<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithLowercaseReturnDescription extends BaseObject
{
    /** @return string the stock keeping unit. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $sku The stock keeping unit.
 */
class ProductWithLowercaseReturnDescription extends BaseObject
{
    /** @return string the stock keeping unit. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
