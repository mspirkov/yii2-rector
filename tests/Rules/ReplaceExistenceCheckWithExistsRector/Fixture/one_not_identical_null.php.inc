<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasRows(Query $query): bool
    {
        return $query->one() !== null;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasRows(Query $query): bool
    {
        return $query->exists();
    }
}
