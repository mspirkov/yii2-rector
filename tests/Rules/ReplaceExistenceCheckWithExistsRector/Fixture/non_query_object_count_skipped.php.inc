<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Source\NonQueryCountable;

class SomeService
{
    public function hasRows(NonQueryCountable $countable): bool
    {
        return $countable->count() > 0;
    }
}
