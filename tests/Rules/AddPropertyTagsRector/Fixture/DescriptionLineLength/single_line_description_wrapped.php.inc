<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

class ProductWithLongSingleLineDescription extends BaseObject
{
    /** @return string A short label used to identify this particular product in listings and search results. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

/**
 * @property-read string $sku A short label used to identify this
 * particular product in listings and
 * search results.
 */
class ProductWithLongSingleLineDescription extends BaseObject
{
    /** @return string A short label used to identify this particular product in listings and search results. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
