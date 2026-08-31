<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 * @todo Some unrelated tag between the property tag and the mixin tag.
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 */
class ProductWithExistingPropertyTagAndMixinTag extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }

    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 * @property-read string $sku
 * @todo Some unrelated tag between the property tag and the mixin tag.
 * @mixin \MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money
 */
class ProductWithExistingPropertyTagAndMixinTag extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }

    public function getSku(): string
    {
        return 'SKU-1';
    }
}
