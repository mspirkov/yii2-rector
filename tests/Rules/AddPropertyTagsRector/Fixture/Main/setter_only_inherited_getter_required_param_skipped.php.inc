<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

class WithRequiredParamInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setRequiredParamValue(int $requiredParamValue): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

/**
 * @property-write int $requiredParamValue
 */
class WithRequiredParamInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setRequiredParamValue(int $requiredParamValue): void
    {
    }
}
