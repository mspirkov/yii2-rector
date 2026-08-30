<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasEnoughRows(Query $query, int $threshold): bool
    {
        return $query->count() > $threshold;
    }
}
