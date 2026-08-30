<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductWithFullyQualifiedRelationClass extends ActiveRecord
{
    public function getCategory()
    {
        return $this->hasOne(\MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category::class, ['id' => 'category_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property-read MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category $category
 */
class ProductWithFullyQualifiedRelationClass extends ActiveRecord
{
    public function getCategory()
    {
        return $this->hasOne(\MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category::class, ['id' => 'category_id']);
    }
}
