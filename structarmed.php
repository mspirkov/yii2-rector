<?php

declare(strict_types=1);

use Boundwize\StructArmed\Architecture;
use Boundwize\StructArmed\Preset\Preset;

return Architecture::define()
    ->withPresets(Preset::PSR4(), Preset::YAGNI(), Preset::CODEQUALITY())

    ->layerPattern('Analyzers', '/^MSpirkov\\\\Yii2\\\\Rector\\\\Analyzers\\\\.*$/')
    ->layerPattern('Helpers', '/^MSpirkov\\\\Yii2\\\\Rector\\\\Helpers\\\\.*$/')
    ->layerPattern('Resolvers', '/^MSpirkov\\\\Yii2\\\\Rector\\\\Resolvers\\\\.*$/')
    ->layerPattern('Rules', '/^MSpirkov\\\\Yii2\\\\Rector\\\\Rules\\\\.*$/')
    ->layerPattern('SetList', '/^MSpirkov\\\\Yii2\\\\Rector\\\\Yii2SetList$/')
    ->layerPattern('ValueObjects', '/^MSpirkov\\\\Yii2\\\\Rector\\\\ValueObjects\\\\.*$/')
    ->ruleset([
        'Analyzers' => [],
        'Helpers' => [],
        'Resolvers' => [],
        'Rules' => ['Analyzers', 'Helpers', 'Resolvers', 'ValueObjects'],
        'SetList' => [],
        'ValueObjects' => [],
    ]);
