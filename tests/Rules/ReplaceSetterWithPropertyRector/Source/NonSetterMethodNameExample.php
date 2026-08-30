<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class NonSetterMethodNameExample extends BaseObject
{
    protected string $prop = '';

    public function updateProp(string $value): void
    {
        $this->prop = $value;
    }
}
