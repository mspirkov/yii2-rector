<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithSetterOnly extends BaseObject
{
    private string $_password;

    public function setPassword(string $password): void
    {
        $this->_password = $password;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write string $password
 */
class ProductWithSetterOnly extends BaseObject
{
    private string $_password;

    public function setPassword(string $password): void
    {
        $this->_password = $password;
    }
}
