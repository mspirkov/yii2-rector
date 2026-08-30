<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class UnionSecondSetterExample extends BaseObject
{
    private $_prop;

    public function setProp(string $value): void
    {
        $this->_prop = $value;
    }
}
