<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

/**
 * @property-write string $prop
 */
class NonYiiSetterExample
{
    private $_prop = '';

    public function setProp(string $value): void
    {
        $this->_prop = $value;
    }
}
