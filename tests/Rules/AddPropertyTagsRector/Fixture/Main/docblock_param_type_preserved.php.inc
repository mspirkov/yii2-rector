<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

class ProductWithDocblockParamType extends BaseObject
{
    private Money $_price;

    /** @param Money $price */
    public function setPrice($price): void
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
class ProductWithDocblockParamType extends BaseObject
{
    private Money $_price;

    /** @param Money $price */
    public function setPrice($price): void
    {
        $this->_price = $price;
    }
}
