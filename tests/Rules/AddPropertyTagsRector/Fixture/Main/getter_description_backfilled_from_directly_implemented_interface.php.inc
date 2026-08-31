<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedGetterInterface;
use yii\base\BaseObject;

class WidgetWithDirectlyImplementedInterfaceGetter extends BaseObject implements DescribedGetterInterface
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\DescribedGetterInterface;
use yii\base\BaseObject;

/**
 * @property-read string $title The item's interface-documented title.
 */
class WidgetWithDirectlyImplementedInterfaceGetter extends BaseObject implements DescribedGetterInterface
{
    public function getTitle(): string
    {
        return 'Widget';
    }
}
