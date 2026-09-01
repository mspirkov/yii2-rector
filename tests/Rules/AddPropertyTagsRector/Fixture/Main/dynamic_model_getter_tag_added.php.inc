<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\DynamicModel;

class ProductDynamicModelWithGetter extends DynamicModel
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\DynamicModel;

/**
 * @property-read string $sku
 */
class ProductDynamicModelWithGetter extends DynamicModel
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
