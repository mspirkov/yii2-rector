<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

class ProductWithLeadingStatementRelation extends ActiveRecord
{
    public function getCategory()
    {
        $link = ['id' => 'category_id'];

        return $this->hasOne(Category::class, $link);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

/**
 * @property-read Category $category
 */
class ProductWithLeadingStatementRelation extends ActiveRecord
{
    public function getCategory()
    {
        $link = ['id' => 'category_id'];

        return $this->hasOne(Category::class, $link);
    }
}
