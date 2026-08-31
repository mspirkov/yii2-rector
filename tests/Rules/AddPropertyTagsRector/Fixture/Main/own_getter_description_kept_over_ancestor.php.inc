<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedGetterBase;

class WidgetWithOwnGetterDescriptionKeepsItOverAncestor extends DescribedGetterBase
{
    /**
     * @return string A custom title just for this widget.
     */
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
 * @property-read string $title A custom title just for this widget.
 */
class WidgetWithOwnGetterDescriptionKeepsItOverAncestor extends DescribedGetterBase
{
    /**
     * @return string A custom title just for this widget.
     */
    public function getTitle(): string
    {
        return 'Widget';
    }
}
