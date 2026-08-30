<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

/**
 * @property-read string $traitProp
 */
trait GetterTraitWithPropertyTag
{
    private $_traitProp = '';

    public function getTraitProp(): string
    {
        return $this->_traitProp;
    }
}
