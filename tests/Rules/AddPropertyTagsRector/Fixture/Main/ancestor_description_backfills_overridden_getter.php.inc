<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedGetterBase;

class WidgetWithOverriddenGetterInheritsAncestorDescription extends DescribedGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedGetterBase;

/**
 * @property-read string $title The item's display title.
 */
class WidgetWithOverriddenGetterInheritsAncestorDescription extends DescribedGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
