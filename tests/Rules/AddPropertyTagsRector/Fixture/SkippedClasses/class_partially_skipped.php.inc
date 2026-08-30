<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read string $name custom description.
 */
class PartiallySkippedProduct extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): int
    {
        return 100;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read string $name custom description.
 * @property-read int $price
 */
class PartiallySkippedProduct extends BaseObject
{
    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): int
    {
        return 100;
    }
}
