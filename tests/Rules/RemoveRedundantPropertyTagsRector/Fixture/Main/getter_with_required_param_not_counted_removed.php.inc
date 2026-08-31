<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 */
class ProductWithGetterRequiredParam extends BaseObject
{
    public function getLegacyCount(int $multiplier): int
    {
        return 5 * $multiplier;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithGetterRequiredParam extends BaseObject
{
    public function getLegacyCount(int $multiplier): int
    {
        return 5 * $multiplier;
    }
}
