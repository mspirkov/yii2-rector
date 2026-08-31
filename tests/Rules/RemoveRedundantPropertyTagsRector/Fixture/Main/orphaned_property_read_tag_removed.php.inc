<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $legacyCount
 */
class ProductWithOrphanedReadTag extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithOrphanedReadTag extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
