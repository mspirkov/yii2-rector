<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

class DescribedGetterBase extends BaseObject
{
    /**
     * @return string The item's display title.
     */
    public function getTitle(): string
    {
        return '';
    }
}
