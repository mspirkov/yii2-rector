<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Connection;
use yii\db\Query;

class SomeService
{
    public function hasRows(Query $query, Connection $db): bool
    {
        return $query->one($db) !== null;
    }
}
