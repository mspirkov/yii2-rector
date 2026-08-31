<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Helpers;

final class StringHelper
{
    public static function collapseWhitespace(string $value): string
    {
        $normalized = preg_replace('/\s*\n\s*\*?\s?/', ' ', $value);

        return trim((string) preg_replace('/\s+/', ' ', (string) $normalized));
    }
}
