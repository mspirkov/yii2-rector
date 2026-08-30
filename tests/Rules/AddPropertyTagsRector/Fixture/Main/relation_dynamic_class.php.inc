<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

class ProductWithDynamicRelationClass extends ActiveRecord
{
    public function getCategory()
    {
        $class = Category::class;

        return $this->hasOne($class, ['id' => 'category_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

/**
 * @property-read mixed $category
 */
class ProductWithDynamicRelationClass extends ActiveRecord
{
    public function getCategory()
    {
        $class = Category::class;

        return $this->hasOne($class, ['id' => 'category_id']);
    }
}
