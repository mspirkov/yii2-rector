<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class ExtraArgumentsExample extends BaseObject
{
    protected string $prop = '';

    public function setProp(string $value, bool $notify = true): void
    {
        $this->prop = $value;
    }
}
