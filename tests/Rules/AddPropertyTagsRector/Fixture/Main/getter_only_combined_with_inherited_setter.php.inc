<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\ColorBase;

class GadgetWithLocalGetterAndInheritedSetter extends ColorBase
{
    public function getColor(): string
    {
        return '';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\ColorBase;

/**
 * @property string $color
 */
class GadgetWithLocalGetterAndInheritedSetter extends ColorBase
{
    public function getColor(): string
    {
        return '';
    }
}
