<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    public function run(): ?Customer
    {
        return Customer::findBySql('SELECT * FROM customer')->where(['status' => 1])->one();
    }
}
