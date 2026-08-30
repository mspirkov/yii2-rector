<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

class NotSkippedProduct extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read string $sku
 */
class NotSkippedProduct extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
