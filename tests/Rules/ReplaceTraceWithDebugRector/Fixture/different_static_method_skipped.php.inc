<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

class SomeService
{
    public function run(): void
    {
        \Yii::error('Something went wrong');
    }
}
