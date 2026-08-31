<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Source\ProductBase;

/**
 * @property-read string $sku
 */
class ProductWithInheritedGetter extends ProductBase
{
}
