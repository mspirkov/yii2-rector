<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;
use yii\db\Connection;

class SomeService
{
    /**
     * @return Order[]
     */
    public function run(Connection $db): array
    {
        return Order::find()->where(['status' => 1])->all($db);
    }
}
