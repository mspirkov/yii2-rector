<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

class ProductWithUnpackedRelationLink extends ActiveRecord
{
    private array $linkArgs = ['id' => 'category_id'];

    public function getCategory()
    {
        return $this->hasOne(Category::class, ...$this->linkArgs);
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
class ProductWithUnpackedRelationLink extends ActiveRecord
{
    private array $linkArgs = ['id' => 'category_id'];

    public function getCategory()
    {
        return $this->hasOne(Category::class, ...$this->linkArgs);
    }
}
