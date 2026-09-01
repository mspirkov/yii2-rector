<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\Model;

/**
 * @property string $legacyName
 */
class ProductModel extends Model
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\Model;

class ProductModel extends Model
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
