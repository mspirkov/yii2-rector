<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\RedisCustomer;

class SomeService
{
    public function run(): ?RedisCustomer
    {
        return RedisCustomer::find()->where(['status' => 1, 'type' => 'vip'])->one();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\RedisCustomer;

class SomeService
{
    public function run(): ?RedisCustomer
    {
        return RedisCustomer::findOne(['status' => 1, 'type' => 'vip']);
    }
}
