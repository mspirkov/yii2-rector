<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\PlainFinder;

class SomeService
{
    public function run(): ?PlainFinder
    {
        return PlainFinder::find()->where(['status' => 1])->one();
    }
}
