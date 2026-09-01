<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantPropertyTagsRector\Source;

use yii\base\BaseObject;

class CustomMagicAccessorBase extends BaseObject
{
    /**
     * @param mixed $name
     *
     * @return mixed
     */
    public function __get($name)
    {
        return null;
    }
}
