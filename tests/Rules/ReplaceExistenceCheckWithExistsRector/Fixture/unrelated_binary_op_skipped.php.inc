<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Fixture;

class SomeService
{
    public function sum(int $a, int $b): int
    {
        return $a + $b;
    }
}
