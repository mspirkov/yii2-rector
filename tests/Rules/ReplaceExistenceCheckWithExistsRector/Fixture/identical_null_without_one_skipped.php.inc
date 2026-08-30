<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

class SomeService
{
    public function isMissing(?int $id): bool
    {
        return $id === null;
    }
}
