<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithUntypedSetter extends BaseObject
{
    private $data;

    public function setData($data): void
    {
        $this->data = $data;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write mixed $data
 */
class ProductWithUntypedSetter extends BaseObject
{
    private $data;

    public function setData($data): void
    {
        $this->data = $data;
    }
}
