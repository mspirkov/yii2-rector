<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithOptionalParamGetter extends BaseObject
{
    public function getName(?string $locale = null): string
    {
        return $locale === null ? 'Widget' : 'Widget (' . $locale . ')';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 */
class ProductWithOptionalParamGetter extends BaseObject
{
    public function getName(?string $locale = null): string
    {
        return $locale === null ? 'Widget' : 'Widget (' . $locale . ')';
    }
}
