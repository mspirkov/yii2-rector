<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasMultipleRows(Query $query): bool
    {
        return $query->count() > 1;
    }
}
