<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Source;

class Encoder
{
    public static function encode(string $content): string
    {
        return $content;
    }
}
