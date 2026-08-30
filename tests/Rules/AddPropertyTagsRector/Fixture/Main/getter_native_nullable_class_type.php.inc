<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

class ProductWithNativeNullableClassGetter extends BaseObject
{
    private ?Money $_price = null;

    public function getPrice(): ?Money
    {
        return $this->_price;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

/**
 * @property-read ?Money $price
 */
class ProductWithNativeNullableClassGetter extends BaseObject
{
    private ?Money $_price = null;

    public function getPrice(): ?Money
    {
        return $this->_price;
    }
}
