<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Source;

class PlainLogger
{
    public static function trace(string $message): void {}
}
