<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithSetterDescriptionFallback extends BaseObject
{
    private string $_name;

    public function getName(): string
    {
        return $this->_name;
    }

    /** @param string $name The product name. */
    public function setName(string $name): void
    {
        $this->_name = $name;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property string $name The product name.
 */
class ProductWithSetterDescriptionFallback extends BaseObject
{
    private string $_name;

    public function getName(): string
    {
        return $this->_name;
    }

    /** @param string $name The product name. */
    public function setName(string $name): void
    {
        $this->_name = $name;
    }
}
