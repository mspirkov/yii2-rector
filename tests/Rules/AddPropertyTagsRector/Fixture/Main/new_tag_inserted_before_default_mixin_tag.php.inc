<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 */
class ProductWithMixinTagGetsNewPropertyInsertedBeforeIt extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 */
class ProductWithMixinTagGetsNewPropertyInsertedBeforeIt extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }
}
