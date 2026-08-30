<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithUnionReturnGetter extends BaseObject
{
    private $_price;

    public function getPrice(): int|string
    {
        return $this->_price;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int|string $price
 */
class ProductWithUnionReturnGetter extends BaseObject
{
    private $_price;

    public function getPrice(): int|string
    {
        return $this->_price;
    }
}
