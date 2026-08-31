<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read int $count
 * @property-read string $name
 * @property-read int $price
 * @property-read bool $active
 * @property-read int $weight
 */
class ProductWithMultiplePropertyTags extends BaseObject
{
    public function getCount(): string
    {
        return '5';
    }

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): float
    {
        return 9.99;
    }

    public function getActive(): bool
    {
        return true;
    }

    public function getWeight(): float
    {
        return 1.5;
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $count
 * @property-read string $name
 * @property-read float $price
 * @property-read bool $active
 * @property-read float $weight
 */
class ProductWithMultiplePropertyTags extends BaseObject
{
    public function getCount(): string
    {
        return '5';
    }

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): float
    {
        return 9.99;
    }

    public function getActive(): bool
    {
        return true;
    }

    public function getWeight(): float
    {
        return 1.5;
    }
}
