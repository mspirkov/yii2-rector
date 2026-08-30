<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithDifferentTypeDescriptions extends BaseObject
{
    /** @var int|string */
    private $_price;

    /** @return int The price in cents. */
    public function getPrice(): int
    {
        return (int) $this->_price;
    }

    /** @param int|string $price The price, as cents or a formatted string. */
    public function setPrice($price): void
    {
        $this->_price = $price;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $price The price in cents.
 * @property-write int|string $price The price, as cents or a formatted string.
 */
class ProductWithDifferentTypeDescriptions extends BaseObject
{
    /** @var int|string */
    private $_price;

    /** @return int The price in cents. */
    public function getPrice(): int
    {
        return (int) $this->_price;
    }

    /** @param int|string $price The price, as cents or a formatted string. */
    public function setPrice($price): void
    {
        $this->_price = $price;
    }
}
