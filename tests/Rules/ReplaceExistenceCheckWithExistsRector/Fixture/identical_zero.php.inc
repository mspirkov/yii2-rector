<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasNoRows(Query $query): bool
    {
        return $query->count() === 0;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasNoRows(Query $query): bool
    {
        return !$query->exists();
    }
}
