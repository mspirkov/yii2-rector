<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

class ProductWithDocblockReturnType extends BaseObject
{
    private Money $_price;

    /** @return Money */
    public function getPrice()
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
 * @property-read Money $price
 */
class ProductWithDocblockReturnType extends BaseObject
{
    private Money $_price;

    /** @return Money */
    public function getPrice()
    {
        return $this->_price;
    }
}
