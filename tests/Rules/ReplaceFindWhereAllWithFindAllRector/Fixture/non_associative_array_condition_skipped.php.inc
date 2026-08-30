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
        // Operator-format condition: integer keys, so findAll() would treat it as a
        // primary key lookup instead of forwarding it to where() unchanged.
        return Order::find()->where(['=', 'status', 1])->all();
    }
}
