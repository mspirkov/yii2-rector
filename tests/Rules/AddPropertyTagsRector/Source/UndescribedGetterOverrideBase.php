<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

class UndescribedGetterOverrideBase extends DescribedGetterBase
{
    public function getTitle(): string
    {
        return '';
    }
}
