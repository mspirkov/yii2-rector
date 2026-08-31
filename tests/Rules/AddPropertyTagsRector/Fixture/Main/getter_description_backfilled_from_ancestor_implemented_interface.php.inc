<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\InterfaceImplementingGetterBase;

class WidgetWithAncestorImplementedInterfaceGetter extends InterfaceImplementingGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\InterfaceImplementingGetterBase;

/**
 * @property-read string $title The item's interface-documented title.
 */
class WidgetWithAncestorImplementedInterfaceGetter extends InterfaceImplementingGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
