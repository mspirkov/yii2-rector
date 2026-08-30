<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class NativeSetterPropertyExample extends BaseObject
{
    protected ?int $prop = null;

    public function setProp(?int $value): void
    {
        $this->prop = $value;
    }
}
