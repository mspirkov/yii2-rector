<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\InheritedSetterPropertyTagExample;

class SomeService
{
    public function run(InheritedSetterPropertyTagExample $example): void
    {
        $example->setTraitProp('a');
        $example->setParentProp('b');
        $example->setInterfaceProp('c');
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\InheritedSetterPropertyTagExample;

class SomeService
{
    public function run(InheritedSetterPropertyTagExample $example): void
    {
        $example->traitProp = 'a';
        $example->parentProp = 'b';
        $example->interfaceProp = 'c';
    }
}
