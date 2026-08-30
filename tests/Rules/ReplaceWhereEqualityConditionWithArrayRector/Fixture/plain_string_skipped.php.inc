<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceWhereEqualityConditionWithArrayRector\Fixture;

use yii\db\Query;

function run(Query $query)
{
    return $query->where('column = 5');
}
