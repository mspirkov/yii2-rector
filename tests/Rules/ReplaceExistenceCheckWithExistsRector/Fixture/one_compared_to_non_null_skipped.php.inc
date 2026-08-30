<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function isDefault(Query $query, array $default): bool
    {
        return $query->one() !== $default;
    }
}
