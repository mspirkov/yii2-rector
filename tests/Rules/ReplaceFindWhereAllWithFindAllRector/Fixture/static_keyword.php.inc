<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use yii\db\ActiveRecord;

class Order extends ActiveRecord
{
    /**
     * @return static[]
     */
    public static function findActive(): array
    {
        return static::find()->where(['status' => 1])->all();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use yii\db\ActiveRecord;

class Order extends ActiveRecord
{
    /**
     * @return static[]
     */
    public static function findActive(): array
    {
        return static::findAll(['status' => 1]);
    }
}
