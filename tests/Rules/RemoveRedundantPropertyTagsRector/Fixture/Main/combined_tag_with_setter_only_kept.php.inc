<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property string $sku
 */
class ProductWithCombinedTagSetterOnly extends BaseObject
{
    public function setSku(string $sku): void
    {
    }
}
