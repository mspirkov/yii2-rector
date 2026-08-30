<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\PlainOrderFinder;

class SomeService
{
    /**
     * @return PlainOrderFinder[]
     */
    public function run(): array
    {
        return PlainOrderFinder::find()->where(['status' => 1])->all();
    }
}
