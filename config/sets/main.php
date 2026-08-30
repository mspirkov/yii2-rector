<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\AddPropertyTagsRector;
use MSpirkov\Yii2\Rector\Rules\MergeModelRulesRector;
use MSpirkov\Yii2\Rector\Rules\RemoveRedundantHtmlEncodeRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceClassnameWithClassRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceExistenceCheckWithExistsRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceFindWhereAllWithFindAllRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceFindWhereOneWithFindOneRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceGetterWithPropertyRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceSetterWithPropertyRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceWhereEqualityConditionWithArrayRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rules([
        AddPropertyTagsRector::class,
        MergeModelRulesRector::class,
        RemoveRedundantHtmlEncodeRector::class,
        ReplaceClassnameWithClassRector::class,
        ReplaceExistenceCheckWithExistsRector::class,
        ReplaceFindWhereAllWithFindAllRector::class,
        ReplaceFindWhereOneWithFindOneRector::class,
        ReplaceGetterWithPropertyRector::class,
        ReplaceSetterWithPropertyRector::class,
        ReplaceWhereEqualityConditionWithArrayRector::class,
    ]);
};
