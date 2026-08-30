<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;

class ProductWithParentRelation extends Category
{
    public function getParentCategory()
    {
        return $this->hasOne(parent::class, ['id' => 'parent_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;

/**
 * @property-read mixed $parentCategory
 */
class ProductWithParentRelation extends Category
{
    public function getParentCategory()
    {
        return $this->hasOne(parent::class, ['id' => 'parent_id']);
    }
}
