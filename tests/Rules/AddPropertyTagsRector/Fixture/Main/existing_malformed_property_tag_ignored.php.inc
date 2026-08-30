<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read
 */
class ProductWithMalformedExistingTag extends BaseObject
{
    public function getName(): string
    {
        return 'name';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read
 * @property-read string $name
 */
class ProductWithMalformedExistingTag extends BaseObject
{
    public function getName(): string
    {
        return 'name';
    }
}
