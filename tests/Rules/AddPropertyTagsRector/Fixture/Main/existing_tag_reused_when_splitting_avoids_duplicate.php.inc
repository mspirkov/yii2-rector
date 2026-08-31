<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 * @property-write string $price
 * @property-read bool $active
 */
class ProductWithSplitTagAndNeighbors extends BaseObject
{
    private $_price;

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): float
    {
        return (float) $this->_price;
    }

    public function setPrice(string $price): void
    {
        $this->_price = $price;
    }

    public function getActive(): bool
    {
        return true;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 * @property-write string $price
 * @property-read float $price
 * @property-read bool $active
 */
class ProductWithSplitTagAndNeighbors extends BaseObject
{
    private $_price;

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): float
    {
        return (float) $this->_price;
    }

    public function setPrice(string $price): void
    {
        $this->_price = $price;
    }

    public function getActive(): bool
    {
        return true;
    }
}
