<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithGetterDescriptionWinning extends BaseObject
{
    private string $_name;

    /** @return string The product name. */
    public function getName(): string
    {
        return $this->_name;
    }

    /** @param string $name A different description from the setter. */
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
class ProductWithGetterDescriptionWinning extends BaseObject
{
    private string $_name;

    /** @return string The product name. */
    public function getName(): string
    {
        return $this->_name;
    }

    /** @param string $name A different description from the setter. */
    public function setName(string $name): void
    {
        $this->_name = $name;
    }
}
