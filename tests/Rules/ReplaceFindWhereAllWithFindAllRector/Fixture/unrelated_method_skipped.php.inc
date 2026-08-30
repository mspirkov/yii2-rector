<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;

class SomeService
{
    public function run(): ?Order
    {
        return Order::find()->where(['status' => 1])->one();
    }
}
