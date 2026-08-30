<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    public function run(): ?Customer
    {
        return Customer::find()->where(['status' => 1, 'type' => 'vip'])->one();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class SomeService
{
    public function run(): ?Customer
    {
        return Customer::findOne(['status' => 1, 'type' => 'vip']);
    }
}

