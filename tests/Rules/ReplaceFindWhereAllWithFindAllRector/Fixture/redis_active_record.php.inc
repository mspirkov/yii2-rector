<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\RedisOrder;

class SomeService
{
    /**
     * @return RedisOrder[]
     */
    public function run(): array
    {
        return RedisOrder::find()->where(['status' => 1, 'type' => 'vip'])->all();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\RedisOrder;

class SomeService
{
    /**
     * @return RedisOrder[]
     */
    public function run(): array
    {
        return RedisOrder::findAll(['status' => 1, 'type' => 'vip']);
    }
}
