<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

class ProductWithDynamicRelationLinkValue extends ActiveRecord
{
    private const CATEGORY_ID_ATTRIBUTE = 'category_id';

    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => self::CATEGORY_ID_ATTRIBUTE]);
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
class ProductWithDynamicRelationLinkValue extends ActiveRecord
{
    private const CATEGORY_ID_ATTRIBUTE = 'category_id';

    public function getCategory()
    {
        return $this->hasOne(Category::class, ['id' => self::CATEGORY_ID_ATTRIBUTE]);
    }
}
