<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $staticCopy
 */
class ProductWithWrongStaticTag extends BaseObject
{
    public function getStaticCopy(): static
    {
        return clone $this;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read static $staticCopy
 */
class ProductWithWrongStaticTag extends BaseObject
{
    public function getStaticCopy(): static
    {
        return clone $this;
    }
}
