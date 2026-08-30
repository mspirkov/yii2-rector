<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithNativeSelfSetter extends BaseObject
{
    public function setSelfCopy(self $value): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write self $selfCopy
 */
class ProductWithNativeSelfSetter extends BaseObject
{
    public function setSelfCopy(self $value): void
    {
    }
}
