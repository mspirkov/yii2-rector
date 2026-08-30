<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use yii\db\ActiveRecord;

class Customer extends ActiveRecord
{
    public static function findActive(): ?self
    {
        return self::find()->where(['status' => 1])->one();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use yii\db\ActiveRecord;

class Customer extends ActiveRecord
{
    public static function findActive(): ?self
    {
        return self::findOne(['status' => 1]);
    }
}

