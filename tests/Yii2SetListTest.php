<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests;

use Iterator;
use MSpirkov\Yii2\Rector\Yii2SetList;
use PHPUnit\Framework\TestCase;
use Rector\Config\RectorConfig;

final class Yii2SetListTest extends TestCase
{
    /**
     * @dataProvider provideSets
     */
    public function testSet(string $set): void
    {
        $this->expectNotToPerformAssertions();

        $rectorConfig = new RectorConfig();
        $rectorConfigBuilder = RectorConfig::configure()->withSets([$set]);
        $rectorConfigBuilder($rectorConfig);
    }

    public static function provideSets(): Iterator
    {
        yield 'deprecation' => [Yii2SetList::DEPRECATION];
        yield 'code quality' => [Yii2SetList::CODE_QUALITY];
        yield 'phpdoc' => [Yii2SetList::PHPDOC];
    }
}
