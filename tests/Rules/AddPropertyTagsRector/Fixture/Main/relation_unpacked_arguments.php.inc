<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

class ProductWithUnpackedRelationArguments extends ActiveRecord
{
    private array $relationArgs = [];

    public function getCategory()
    {
        return $this->hasOne(...$this->relationArgs);
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\db\ActiveRecord;

/**
 * @property-read mixed $category
 */
class ProductWithUnpackedRelationArguments extends ActiveRecord
{
    private array $relationArgs = [];

    public function getCategory()
    {
        return $this->hasOne(...$this->relationArgs);
    }
}
