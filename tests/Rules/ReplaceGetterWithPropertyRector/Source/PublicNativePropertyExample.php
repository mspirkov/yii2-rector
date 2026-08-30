<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

class PublicNativePropertyExample extends BaseObject
{
    public string $prop = '';

    public function getProp(): string
    {
        return $this->prop;
    }
}
