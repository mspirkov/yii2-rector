<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $sku
 */
class ProductWithReadTagButOnlySetter extends BaseObject
{
    public function setSku(string $sku): void
    {
    }
}
