<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\ReplaceCacheMultiMethodAliasesRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceClassnameWithClassRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceExitCodeConstantRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceGetHasChangedWithIsChangedRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceTraceWithDebugRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        ReplaceCacheMultiMethodAliasesRector::class,
        ReplaceClassnameWithClassRector::class,
        ReplaceExitCodeConstantRector::class,
        ReplaceGetHasChangedWithIsChangedRector::class,
        ReplaceTraceWithDebugRector::class,
    ]);
};
