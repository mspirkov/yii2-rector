<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;
use yii\db\Connection;

class SomeService
{
    public function run(Connection $db): ?Customer
    {
        return Customer::find()->where(['status' => 1])->one($db);
    }
}
