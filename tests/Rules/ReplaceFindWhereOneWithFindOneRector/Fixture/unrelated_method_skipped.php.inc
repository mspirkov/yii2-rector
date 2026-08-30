<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    public function run(): array
    {
        return Customer::find()->where(['status' => 1])->all();
    }
}
