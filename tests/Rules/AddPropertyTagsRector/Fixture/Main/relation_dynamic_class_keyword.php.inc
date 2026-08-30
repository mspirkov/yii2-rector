<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductWithDynamicClassKeywordRelation extends ActiveRecord
{
    private $relatedInstance;

    public function getCategory()
    {
        return $this->hasOne($this->relatedInstance::class, ['id' => 'category_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property-read mixed $category
 */
class ProductWithDynamicClassKeywordRelation extends ActiveRecord
{
    private $relatedInstance;

    public function getCategory()
    {
        return $this->hasOne($this->relatedInstance::class, ['id' => 'category_id']);
    }
}
