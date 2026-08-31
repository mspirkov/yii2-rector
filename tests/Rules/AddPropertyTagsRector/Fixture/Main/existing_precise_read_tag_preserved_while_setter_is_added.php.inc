<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $data
 */
class ProductWithPreciseReadTagGainsNewSetter extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }

    public function setData(string $data): void
    {
        $this->data = $data;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $data
 * @property-write string $data
 */
class ProductWithPreciseReadTagGainsNewSetter extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }

    public function setData(string $data): void
    {
        $this->data = $data;
    }
}
