<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

class ProductWithNativeClassSetter extends BaseObject
{
    private Money $_price;

    public function setPrice(Money $price): void
    {
        $this->_price = $price;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

/**
 * @property-write Money $price
 */
class ProductWithNativeClassSetter extends BaseObject
{
    private Money $_price;

    public function setPrice(Money $price): void
    {
        $this->_price = $price;
    }
}
