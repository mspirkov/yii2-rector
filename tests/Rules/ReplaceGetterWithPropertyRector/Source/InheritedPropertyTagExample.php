<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

class InheritedPropertyTagExample extends GetterParentWithPropertyTag implements GetterInterfaceWithPropertyTag
{
    use GetterTraitWithPropertyTag;

    private $_interfaceProp = '';

    public function getInterfaceProp(): string
    {
        return $this->_interfaceProp;
    }
}
