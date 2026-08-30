<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read string $prop
 */
class WithArgumentsExample extends BaseObject
{
    private $_prop = '';

    public function getProp(string $default = ''): string
    {
        return $this->_prop !== '' ? $this->_prop : $default;
    }
}
