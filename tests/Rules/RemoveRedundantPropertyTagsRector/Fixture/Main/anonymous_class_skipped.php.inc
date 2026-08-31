<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

function createAnonymousProduct()
{
    return new /**
     * @property-read int $legacyCount
     */
    class extends BaseObject {
        public function getSku(): string
        {
            return 'SKU-1';
        }
    };
}
