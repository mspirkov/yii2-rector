<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write float $legacyDiscount
 */
class ProductWithSetterRequiredSecondParam extends BaseObject
{
    public function setLegacyDiscount(float $discount, bool $apply): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithSetterRequiredSecondParam extends BaseObject
{
    public function setLegacyDiscount(float $discount, bool $apply): void
    {
    }
}
