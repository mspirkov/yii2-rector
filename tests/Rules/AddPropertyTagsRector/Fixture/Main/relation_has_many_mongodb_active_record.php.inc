<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\mongodb\ActiveRecord;

class ProductWithMongodbCategoriesRelation extends ActiveRecord
{
    public function getCategories()
    {
        return $this->hasMany(Category::class, ['product_id' => 'id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\mongodb\ActiveRecord;

/**
 * @property-read Category[] $categories
 */
class ProductWithMongodbCategoriesRelation extends ActiveRecord
{
    public function getCategories()
    {
        return $this->hasMany(Category::class, ['product_id' => 'id']);
    }
}
