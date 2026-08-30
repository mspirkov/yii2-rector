<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

class WithStaticInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setStaticValue(int $staticValue): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

/**
 * @property-write int $staticValue
 */
class WithStaticInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setStaticValue(int $staticValue): void
    {
    }
}
