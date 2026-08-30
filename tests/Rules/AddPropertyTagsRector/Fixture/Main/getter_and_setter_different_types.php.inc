<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithDifferentAccessorTypes extends BaseObject
{
    private float $_price;

    public function getPrice(): string
    {
        return (string) $this->_price;
    }

    public function setPrice(float $price): void
    {
        $this->_price = $price;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $price
 * @property-write float $price
 */
class ProductWithDifferentAccessorTypes extends BaseObject
{
    private float $_price;

    public function getPrice(): string
    {
        return (string) $this->_price;
    }

    public function setPrice(float $price): void
    {
        $this->_price = $price;
    }
}
