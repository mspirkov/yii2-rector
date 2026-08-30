<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveQuery;
use yii\db\ActiveRecord;

class ProductWithDescribedCategoryRelation extends ActiveRecord
{
    /**
     * @return ActiveQuery The category this product belongs to.
     */
    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => 'category_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveQuery;
use yii\db\ActiveRecord;

/**
 * @property-read Category|null $category The category this product belongs to.
 */
class ProductWithDescribedCategoryRelation extends ActiveRecord
{
    /**
     * @return ActiveQuery The category this product belongs to.
     */
    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => 'category_id']);
    }
}
