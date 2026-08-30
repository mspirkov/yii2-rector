<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithProtectedSetter extends BaseObject
{
    private string $_internalToken = '';

    protected function setInternalToken(string $internalToken): void
    {
        $this->_internalToken = $internalToken;
    }
}
