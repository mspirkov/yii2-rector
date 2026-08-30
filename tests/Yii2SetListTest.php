<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests;

use MSpirkov\Yii2\Rector\Yii2SetList;
use PHPUnit\Framework\TestCase;
use Rector\Config\RectorConfig;

final class Yii2SetListTest extends TestCase
{
    public function testMainSet(): void
    {
        $rectorConfig = new RectorConfig();
        $rectorConfigBuilder = RectorConfig::configure()->withSets([Yii2SetList::MAIN]);
        $rectorConfigBuilder($rectorConfig);

        $rules = array_keys($rectorConfig->getBindings());
        self::assertNotEmpty($rules);

        foreach ($rules as $rule) {
            self::assertIsString($rule);
            self::assertStringContainsString('MSpirkov\Yii2\Rector\Rules\\', $rule);
        }
    }
}
