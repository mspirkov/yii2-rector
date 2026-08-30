<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $count
 */
class ProductWithCorrectExistingTag extends BaseObject
{
    public function getCount(): string
    {
        return '5';
    }
}
