<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AddPropertyTagsRectorDescriptionLineLengthTest extends AbstractRectorTestCase
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
        return self::yieldFilesFromDirectory(__DIR__ . '/Fixture/DescriptionLineLength');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/Config/description_line_length_configured_rule.php';
    }
}
