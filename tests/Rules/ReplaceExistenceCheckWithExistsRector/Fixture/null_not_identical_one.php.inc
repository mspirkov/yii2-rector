<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\db\Query;

class SomeService
{
    public function hasRows(Query $query): bool
    {
        return null !== $query->one();
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
