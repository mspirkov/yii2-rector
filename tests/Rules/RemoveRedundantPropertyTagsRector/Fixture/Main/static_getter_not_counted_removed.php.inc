<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 */
class ProductWithStaticGetter extends BaseObject
{
    public static function getLegacyCount(): int
    {
        return 5;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithStaticGetter extends BaseObject
{
    public static function getLegacyCount(): int
    {
        return 5;
    }
}
