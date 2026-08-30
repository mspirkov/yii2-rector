<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

/**
 * @property-read string $prop
 */
class NonYiiExample
{
    private $_prop = '';

    public function getProp(): string
    {
        return $this->_prop;
    }
}
