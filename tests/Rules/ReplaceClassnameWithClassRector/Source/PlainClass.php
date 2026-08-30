<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceClassnameWithClassRector\Source;

class PlainClass
{
    public static function className(): string
    {
        return 'plain';
    }
}
