<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write float $legacyDiscount
 */
class ProductWithProtectedSetter extends BaseObject
{
    protected function setLegacyDiscount(float $discount): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithProtectedSetter extends BaseObject
{
    protected function setLegacyDiscount(float $discount): void
    {
    }
}
