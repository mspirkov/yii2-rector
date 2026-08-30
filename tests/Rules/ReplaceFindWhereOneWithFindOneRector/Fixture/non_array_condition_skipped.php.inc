<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    /**
     * @param array<string, mixed> $condition
     */
    public function run(array $condition): ?Customer
    {
        return Customer::find()->where($condition)->one();
    }
}
