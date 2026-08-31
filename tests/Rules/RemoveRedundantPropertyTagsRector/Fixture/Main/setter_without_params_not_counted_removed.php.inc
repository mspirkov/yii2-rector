<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write float $legacyDiscount
 */
class ProductWithSetterWithoutParams extends BaseObject
{
    public function setLegacyDiscount(): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithSetterWithoutParams extends BaseObject
{
    public function setLegacyDiscount(): void
    {
    }
}
