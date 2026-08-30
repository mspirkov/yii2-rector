<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use yii\db\ActiveRecord;

class Order extends ActiveRecord
{
    /**
     * @return self[]
     */
    public static function findActive(): array
    {
        return self::find()->where(['status' => 1])->all();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use yii\db\ActiveRecord;

class Order extends ActiveRecord
{
    /**
     * @return self[]
     */
    public static function findActive(): array
    {
        return self::findAll(['status' => 1]);
    }
}
