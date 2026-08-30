<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $count The number of items in stock.
 */
class ProductWithCorrectExistingTagDescription extends BaseObject
{
    /** @return string The number of items in stock. */
    public function getCount(): string
    {
        return '5';
    }
}
