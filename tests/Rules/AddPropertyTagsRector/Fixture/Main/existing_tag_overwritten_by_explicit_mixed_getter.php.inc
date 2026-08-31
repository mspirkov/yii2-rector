<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $data
 */
class ProductWithExplicitMixedGetterOverwritesExistingTag extends BaseObject
{
    private $data;

    /** @return mixed */
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
class ProductWithExplicitMixedGetterOverwritesExistingTag extends BaseObject
{
    private $data;

    /** @return mixed */
    public function getData()
    {
        return $this->data;
    }
}
