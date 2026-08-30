<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

class ProductWithChainedRelationCall extends ActiveRecord
{
    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => 'category_id'])->inverseOf('products');
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

/**
 * @property-read Category|null $category
 */
class ProductWithChainedRelationCall extends ActiveRecord
{
    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => 'category_id'])->inverseOf('products');
    }
}
