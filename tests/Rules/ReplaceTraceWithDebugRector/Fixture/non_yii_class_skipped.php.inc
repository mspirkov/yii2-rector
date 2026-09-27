<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Source\PlainLogger;

class SomeService
{
    public function run(): void
    {
        PlainLogger::trace('Some message');
    }
}
