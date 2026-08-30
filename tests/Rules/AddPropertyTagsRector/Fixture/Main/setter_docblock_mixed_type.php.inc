<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithDocblockMixedSetter extends BaseObject
{
    private $data;

    /** @param mixed $data */
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
class ProductWithDocblockMixedSetter extends BaseObject
{
    private $data;

    /** @param mixed $data */
    public function setData($data): void
    {
        $this->data = $data;
    }
}
