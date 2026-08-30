<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

/**
 * @property-write string $traitProp
 */
trait SetterTraitWithPropertyTag
{
    private $_traitProp = '';

    public function setTraitProp(string $value): void
    {
        $this->_traitProp = $value;
    }
}
