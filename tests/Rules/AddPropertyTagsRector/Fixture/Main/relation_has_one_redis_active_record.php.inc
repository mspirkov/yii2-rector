<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\redis\ActiveQuery;
use yii\redis\ActiveRecord;

class ProductWithRedisCategoryRelation extends ActiveRecord
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
use yii\redis\ActiveQuery;
use yii\redis\ActiveRecord;

/**
 * @property-read Category|null $category The category this product belongs to.
 */
class ProductWithRedisCategoryRelation extends ActiveRecord
{
    /**
     * @return ActiveQuery The category this product belongs to.
     */
    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => 'category_id']);
    }
}
