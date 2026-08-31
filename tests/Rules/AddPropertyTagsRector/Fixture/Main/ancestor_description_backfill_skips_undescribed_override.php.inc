<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\UndescribedGetterOverrideBase;

class WidgetWithGrandparentDescriptionBackfilled extends UndescribedGetterOverrideBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\UndescribedGetterOverrideBase;

/**
 * @property-read string $title The item's display title.
 */
class WidgetWithGrandparentDescriptionBackfilled extends UndescribedGetterOverrideBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
