<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithUnpunctuatedReturnDescription extends BaseObject
{
    /** @return string The stock keeping unit */
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
class ProductWithUnpunctuatedReturnDescription extends BaseObject
{
    /** @return string The stock keeping unit */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
