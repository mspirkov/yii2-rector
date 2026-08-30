<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

class DynamicMethodNameExample extends BaseObject
{
    protected string $prop = '';

    public function getProp(): string
    {
        return $this->prop;
    }
}
