<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductWithSelfRelation extends ActiveRecord
{
    public function getSibling()
    {
        return $this->hasOne(self::class, ['id' => 'sibling_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property-read self $sibling
 */
class ProductWithSelfRelation extends ActiveRecord
{
    public function getSibling()
    {
        return $this->hasOne(self::class, ['id' => 'sibling_id']);
    }
}
