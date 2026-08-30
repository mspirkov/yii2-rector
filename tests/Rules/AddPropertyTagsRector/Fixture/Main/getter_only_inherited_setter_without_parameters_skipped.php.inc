<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

class WithParameterlessInheritedSetterCounterpart extends AccessorEdgeCasesBase
{
    public function getNoParamValue(): int
    {
        return 0;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

/**
 * @property-read int $noParamValue
 */
class WithParameterlessInheritedSetterCounterpart extends AccessorEdgeCasesBase
{
    public function getNoParamValue(): int
    {
        return 0;
    }
}
