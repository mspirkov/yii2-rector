<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\MongodbCustomer;

class SomeService
{
    public function run(): ?MongodbCustomer
    {
        return MongodbCustomer::find()->where(['status' => 1, 'type' => 'vip'])->one();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\MongodbCustomer;

class SomeService
{
    public function run(): ?MongodbCustomer
    {
        return MongodbCustomer::findOne(['status' => 1, 'type' => 'vip']);
    }
}
