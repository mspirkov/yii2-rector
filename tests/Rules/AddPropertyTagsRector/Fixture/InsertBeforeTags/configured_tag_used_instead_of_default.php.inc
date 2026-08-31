<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\InsertBeforeTags;

use yii\base\BaseObject;

/**
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 * @method void doSomething()
 */
class ProductWithConfiguredMethodTag extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\InsertBeforeTags;

use yii\base\BaseObject;

/**
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 * @property-read string $name
 * @method void doSomething()
 */
class ProductWithConfiguredMethodTag extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }
}
