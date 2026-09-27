<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\MongodbOrder;

class SomeService
{
    /**
     * @return MongodbOrder[]
     */
    public function run(): array
    {
        return MongodbOrder::find()->where(['status' => 1, 'type' => 'vip'])->all();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\MongodbOrder;

class SomeService
{
    /**
     * @return MongodbOrder[]
     */
    public function run(): array
    {
        return MongodbOrder::findAll(['status' => 1, 'type' => 'vip']);
    }
}
