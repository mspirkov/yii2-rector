<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

trait TitleTrait
{
    /**
     * @return string A trait-provided title.
     */
    public function getTitle(): string
    {
        return '';
    }
}
