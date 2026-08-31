<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\RemoveRedundantPropertyTagsRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(RemoveRedundantPropertyTagsRector::class, [
        RemoveRedundantPropertyTagsRector::SKIPPED_CLASSES => [
            'MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\SkippedClasses\SkippedProduct',
            'MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\SkippedClasses\PartiallySkippedProduct' => ['legacyCount'],
        ],
    ]);
};
