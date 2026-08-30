<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;

class SomeService
{
    /**
     * @return Order[]
     */
    public function run(): array
    {
        return Order::find()->where(['status' => 1, 'type' => 'vip'])->all();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;

class SomeService
{
    /**
     * @return Order[]
     */
    public function run(): array
    {
        return Order::findAll(['status' => 1, 'type' => 'vip']);
    }
}
