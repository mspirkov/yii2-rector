<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $count
 */
class ProductWithWrongExistingTag extends BaseObject
{
    public function getCount(): string
    {
        return '5';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $count
 */
class ProductWithWrongExistingTag extends BaseObject
{
    public function getCount(): string
    {
        return '5';
    }
}
