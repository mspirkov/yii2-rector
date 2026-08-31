<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector;

use InvalidArgumentException;
use MSpirkov\Yii2\Rector\Rules\RemoveRedundantPropertyTagsRector;
use Rector\Testing\PHPUnit\AbstractLazyTestCase;

final class RemoveRedundantPropertyTagsRectorConfigureTest extends AbstractLazyTestCase
{
    public function testSkippedClassesMustBeAnArray(): void
    {
        $rule = $this->make(RemoveRedundantPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([RemoveRedundantPropertyTagsRector::SKIPPED_CLASSES => 'notAnArray']);
    }

    public function testNumericKeyRequiresAStringValue(): void
    {
        $rule = $this->make(RemoveRedundantPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([RemoveRedundantPropertyTagsRector::SKIPPED_CLASSES => [['NotAString']]]);
    }

    public function testClassKeyRequiresAnArrayValue(): void
    {
        $rule = $this->make(RemoveRedundantPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([RemoveRedundantPropertyTagsRector::SKIPPED_CLASSES => ['SomeClass' => 'notAList']]);
    }

    public function testClassKeyPropertyListMustContainOnlyStrings(): void
    {
        $rule = $this->make(RemoveRedundantPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([RemoveRedundantPropertyTagsRector::SKIPPED_CLASSES => ['SomeClass' => ['validProperty', 123]]]);
    }
}
