<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

class NativePropertyExample extends BaseObject
{
    protected ?int $prop = null;

    public function getProp(): ?int
    {
        return $this->prop;
    }
}
