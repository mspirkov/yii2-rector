<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\TraitedGetterBase;

class WidgetWithOverriddenTraitGetterHasNoBackfilledDescription extends TraitedGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\TraitedGetterBase;

/**
 * @property-read string $title
 */
class WidgetWithOverriddenTraitGetterHasNoBackfilledDescription extends TraitedGetterBase
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
