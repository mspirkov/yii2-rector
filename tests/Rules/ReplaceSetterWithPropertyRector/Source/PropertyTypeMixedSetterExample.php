<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write mixed $prop
 */
class PropertyTypeMixedSetterExample extends BaseObject
{
    private string $prop;

    public function setProp(string $value): void
    {
        $this->prop = $value;
    }
}
