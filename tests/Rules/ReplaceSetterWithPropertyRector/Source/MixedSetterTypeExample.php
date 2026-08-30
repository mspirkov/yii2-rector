<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write mixed $prop
 */
class MixedSetterTypeExample extends BaseObject
{
    private $prop;

    /**
     * @param mixed $value
     */
    public function setProp($value): void
    {
        $this->prop = $value;
    }
}
