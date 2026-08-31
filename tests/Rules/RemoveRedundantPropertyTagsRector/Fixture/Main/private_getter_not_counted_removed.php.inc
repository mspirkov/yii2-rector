<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 */
class ProductWithPrivateGetter extends BaseObject
{
    private function getLegacyCount(): int
    {
        return 5;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithPrivateGetter extends BaseObject
{
    private function getLegacyCount(): int
    {
        return 5;
    }
}
