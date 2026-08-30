<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $selfCopy
 */
class ProductWithWrongSelfTag extends BaseObject
{
    public function getSelfCopy(): self
    {
        return clone $this;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read self $selfCopy
 */
class ProductWithWrongSelfTag extends BaseObject
{
    public function getSelfCopy(): self
    {
        return clone $this;
    }
}
