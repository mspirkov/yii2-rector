<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write string $sku
 */
class ProductWithWriteTagButOnlyGetter extends BaseObject
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

class ProductWithWriteTagButOnlyGetter extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
