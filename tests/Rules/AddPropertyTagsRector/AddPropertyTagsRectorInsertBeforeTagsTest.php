<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AddPropertyTagsRectorInsertBeforeTagsTest extends AbstractRectorTestCase
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
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture/InsertBeforeTags');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/Config/insert_before_tags_configured_rule.php';
    }
}
