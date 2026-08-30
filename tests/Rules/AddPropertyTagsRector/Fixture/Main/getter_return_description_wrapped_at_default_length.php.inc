<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithDescriptionOverDefaultWrapLength extends BaseObject
{
    /** @return string Returns the fully formatted display name for this product, including any active discount badge suffix if one currently applies. */
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
 * @property-read string $name Returns the fully formatted display name for this product, including any active
 * discount badge suffix if one currently applies.
 */
class ProductWithDescriptionOverDefaultWrapLength extends BaseObject
{
    /** @return string Returns the fully formatted display name for this product, including any active discount badge suffix if one currently applies. */
    public function getName(): string
    {
        return 'Widget';
    }
}
