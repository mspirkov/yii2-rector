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
        return Order::findBySql('SELECT * FROM order')->where(['status' => 1])->all();
    }
}
