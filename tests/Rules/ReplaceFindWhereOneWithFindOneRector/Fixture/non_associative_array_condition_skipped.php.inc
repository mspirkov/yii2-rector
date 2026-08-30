<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    public function run(): ?Customer
    {
        // Operator-format condition: integer keys, so findOne() would treat it as a
        // primary key lookup instead of forwarding it to where() unchanged.
        return Customer::find()->where(['=', 'status', 1])->one();
    }
}
