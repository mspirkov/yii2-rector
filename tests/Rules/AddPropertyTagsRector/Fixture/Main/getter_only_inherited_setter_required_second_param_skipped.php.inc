<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

class WithRequiredSecondParamInheritedSetterCounterpart extends AccessorEdgeCasesBase
{
    public function getRequiredSecondParamValue(): int
    {
        return 0;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

/**
 * @property-read int $requiredSecondParamValue
 */
class WithRequiredSecondParamInheritedSetterCounterpart extends AccessorEdgeCasesBase
{
    public function getRequiredSecondParamValue(): int
    {
        return 0;
    }
}
