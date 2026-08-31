<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * A product model.
 *
 * @property-read int $legacyCount
 * @since 1.0
 */
class ProductWithNonPropertyTag extends BaseObject
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

/**
 * A product model.
 *
 * @since 1.0
 */
class ProductWithNonPropertyTag extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
