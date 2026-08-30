<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\InheritedPropertyTagExample;

class SomeService
{
    public function run(InheritedPropertyTagExample $example): string
    {
        return $example->getTraitProp() . $example->getParentProp() . $example->getInterfaceProp();
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source\InheritedPropertyTagExample;

class SomeService
{
    public function run(InheritedPropertyTagExample $example): string
    {
        return $example->traitProp . $example->parentProp . $example->interfaceProp;
    }
}
