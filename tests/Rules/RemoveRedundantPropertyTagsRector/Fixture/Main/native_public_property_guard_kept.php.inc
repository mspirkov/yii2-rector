<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property int $legacyCount
 */
class ProductWithNativePublicProperty extends BaseObject
{
    public int $legacyCount = 0;
}
