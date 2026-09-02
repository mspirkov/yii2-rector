<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\SkippedClasses;

use yii\base\BaseObject;

/**
 * @property-read string $name custom description.
 */
class PartiallySkippedProduct extends BaseObject
{
    private array $colors = [];

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): int
    {
        return 100;
    }

    public function setColor(string $color): void
    {
        $this->colors[] = $color;
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
    private array $colors = [];

    public function getName(): string
    {
        return 'Widget';
    }

    public function getPrice(): int
    {
        return 100;
    }

    public function setColor(string $color): void
    {
        $this->colors[] = $color;
    }
}
