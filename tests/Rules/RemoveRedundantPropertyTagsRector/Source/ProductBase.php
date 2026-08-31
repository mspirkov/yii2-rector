<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Source;

use yii\base\BaseObject;

class ProductBase extends BaseObject
{
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
