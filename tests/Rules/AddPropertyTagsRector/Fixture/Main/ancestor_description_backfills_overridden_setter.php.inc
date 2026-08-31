<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedSetterBase;

class WidgetWithOverriddenSetterInheritsAncestorDescription extends DescribedSetterBase
{
    public function setLabel(string $label): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedSetterBase;

/**
 * @property-write string $label The new display label.
 */
class WidgetWithOverriddenSetterInheritsAncestorDescription extends DescribedSetterBase
{
    public function setLabel(string $label): void
    {
    }
}
