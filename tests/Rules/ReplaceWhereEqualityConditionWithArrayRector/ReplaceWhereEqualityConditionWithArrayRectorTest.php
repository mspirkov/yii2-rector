<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceWhereEqualityConditionWithArrayRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class ReplaceWhereEqualityConditionWithArrayRectorTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    public static function provideData(): Iterator
    {
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/Config/configured_rule.php';
    }
}
