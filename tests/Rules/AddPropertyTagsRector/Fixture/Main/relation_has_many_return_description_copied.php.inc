<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveQuery;
use yii\db\ActiveRecord;

class ProductWithDescribedCategoriesRelation extends ActiveRecord
{
    /**
     * @return ActiveQuery The categories this product is listed under.
     */
    public function getCategories()
    {
        return $this->hasMany(Category::class, ['product_id' => 'id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveQuery;
use yii\db\ActiveRecord;

/**
 * @property-read Category[] $categories The categories this product is listed under.
 */
class ProductWithDescribedCategoriesRelation extends ActiveRecord
{
    /**
     * @return ActiveQuery The categories this product is listed under.
     */
    public function getCategories()
    {
        return $this->hasMany(Category::class, ['product_id' => 'id']);
    }
}
