<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\ZeroArgSetterAncestorBase;

class WidgetOverridingZeroArgAncestorSetter extends ZeroArgSetterAncestorBase
{
    public function setLabel(string $label = ''): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\ZeroArgSetterAncestorBase;

/**
 * @property-write string $label
 */
class WidgetOverridingZeroArgAncestorSetter extends ZeroArgSetterAncestorBase
{
    public function setLabel(string $label = ''): void
    {
    }
}
