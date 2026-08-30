<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceWhereEqualityConditionWithArrayRector\Fixture;

use yii\db\Query;

function run(Query $query, $value, $other)
{
    return $query->where("column = $value AND extra = $other");
}
