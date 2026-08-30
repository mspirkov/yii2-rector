<?php

declare(strict_types=1);

use MSpirkov\Yii2\Rector\Rules\ReplaceFindWhereAllWithFindAllRector;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->rule(ReplaceFindWhereAllWithFindAllRector::class);
};
