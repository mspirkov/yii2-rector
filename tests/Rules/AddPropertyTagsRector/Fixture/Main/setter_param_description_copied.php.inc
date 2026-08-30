<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithSetterParamDescription extends BaseObject
{
    /** @param string $sku The stock keeping unit. */
    public function setSku(string $sku): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write string $sku The stock keeping unit.
 */
class ProductWithSetterParamDescription extends BaseObject
{
    /** @param string $sku The stock keeping unit. */
    public function setSku(string $sku): void
    {
    }
}
