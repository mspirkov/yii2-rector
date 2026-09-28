<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\AddPropertyTagsRector;
use MSpirkov\Yii2\Rector\Rules\RemoveRedundantPropertyTagsRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        AddPropertyTagsRector::class,
        RemoveRedundantPropertyTagsRector::class,
    ]);
};
