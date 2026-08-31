<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector;

use InvalidArgumentException;
use MSpirkov\Yii2\Rector\Rules\AddPropertyTagsRector;
use Rector\Testing\PHPUnit\AbstractLazyTestCase;

final class AddPropertyTagsRectorConfigureTest extends AbstractLazyTestCase
{
    public function testSkippedClassesMustBeAnArray(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::SKIPPED_CLASSES => 'notAnArray']);
    }

    public function testNumericKeyRequiresAStringValue(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::SKIPPED_CLASSES => [['NotAString']]]);
    }

    public function testClassKeyRequiresAnArrayValue(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::SKIPPED_CLASSES => ['SomeClass' => 'notAList']]);
    }

    public function testClassKeyPropertyListMustContainOnlyStrings(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::SKIPPED_CLASSES => ['SomeClass' => ['validProperty', 123]]]);
    }

    public function testInsertBeforeTagsMustBeAnArray(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::INSERT_BEFORE_TAGS => 'notAnArray']);
    }

    public function testInsertBeforeTagsMustContainOnlyStrings(): void
    {
        $rule = $this->make(AddPropertyTagsRector::class);

        self::expectException(InvalidArgumentException::class);

        $rule->configure([AddPropertyTagsRector::INSERT_BEFORE_TAGS => ['@mixin', 123]]);
    }
}
