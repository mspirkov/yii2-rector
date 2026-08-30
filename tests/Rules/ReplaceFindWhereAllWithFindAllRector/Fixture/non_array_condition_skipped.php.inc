<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;

class SomeService
{
    /**
     * @param array<string, mixed> $condition
     * @return Order[]
     */
    public function run(array $condition): array
    {
        return Order::find()->where($condition)->all();
    }
}
