<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

function createAnonymousProduct()
{
    return new class extends BaseObject {
        public function getName(): string
        {
            return 'name';
        }
    };
}
