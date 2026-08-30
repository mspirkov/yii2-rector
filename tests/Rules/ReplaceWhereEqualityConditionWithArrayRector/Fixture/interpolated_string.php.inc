<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceWhereEqualityConditionWithArrayRector\Fixture;

use yii\db\Query;

function run(Query $query, $value)
{
    return $query->where("column = $value");
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceWhereEqualityConditionWithArrayRector\Fixture;

use yii\db\Query;

function run(Query $query, $value)
{
    return $query->where(['column' => $value]);
}
