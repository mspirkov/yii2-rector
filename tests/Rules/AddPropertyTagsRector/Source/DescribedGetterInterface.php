<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

interface DescribedGetterInterface
{
    /**
     * @return string The item's interface-documented title.
     */
    public function getTitle(): string;
}
