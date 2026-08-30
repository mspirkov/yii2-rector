<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

class WithProtectedInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setProtectedValue(int $protectedValue): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\AccessorEdgeCasesBase;

/**
 * @property-write int $protectedValue
 */
class WithProtectedInheritedGetterCounterpart extends AccessorEdgeCasesBase
{
    public function setProtectedValue(int $protectedValue): void
    {
    }
}
