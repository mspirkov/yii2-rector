<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\AddPropertyTagsRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(AddPropertyTagsRector::class, [
        AddPropertyTagsRector::DESCRIPTION_LINE_LENGTH => 40,
    ]);
};
