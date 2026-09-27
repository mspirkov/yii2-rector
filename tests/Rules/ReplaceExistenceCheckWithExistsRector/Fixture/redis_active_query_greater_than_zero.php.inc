<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\redis\ActiveQuery;

class SomeService
{
    public function hasRows(ActiveQuery $query): bool
    {
        return $query->count() > 0;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use yii\redis\ActiveQuery;

class SomeService
{
    public function hasRows(ActiveQuery $query): bool
    {
        return $query->exists();
    }
}
