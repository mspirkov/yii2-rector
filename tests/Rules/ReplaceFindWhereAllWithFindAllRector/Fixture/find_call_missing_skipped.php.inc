<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function run(Query $query)
    {
        return $query->where(['status' => 1])->all();
    }
}
