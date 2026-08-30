<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

class InheritedSetterPropertyTagExample extends SetterParentWithPropertyTag implements SetterInterfaceWithPropertyTag
{
    use SetterTraitWithPropertyTag;

    private $_interfaceProp = '';

    public function setInterfaceProp(string $value): void
    {
        $this->_interfaceProp = $value;
    }
}
