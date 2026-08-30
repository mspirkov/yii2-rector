<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithUntypedGetter extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read mixed $data
 */
class ProductWithUntypedGetter extends BaseObject
{
    private $data;

    public function getData()
    {
        return $this->data;
    }
}
