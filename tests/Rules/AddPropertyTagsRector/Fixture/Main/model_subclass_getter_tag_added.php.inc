<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\Model;

class ProductModelWithGetter extends Model
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\Model;

/**
 * @property-read string $sku
 */
class ProductModelWithGetter extends Model
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
