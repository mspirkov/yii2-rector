<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductWithStaticRelation extends ActiveRecord
{
    public function getSibling()
    {
        return $this->hasOne(static::class, ['id' => 'sibling_id']);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property-read static $sibling
 */
class ProductWithStaticRelation extends ActiveRecord
{
    public function getSibling()
    {
        return $this->hasOne(static::class, ['id' => 'sibling_id']);
    }
}
