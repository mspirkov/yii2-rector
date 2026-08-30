<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class PublicNativeSetterPropertyExample extends BaseObject
{
    public string $prop = '';

    public function setProp(string $value): void
    {
        $this->prop = $value;
    }
}
