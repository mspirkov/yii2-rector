<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write int $prop
 */
class SetterTypeMismatchExample extends BaseObject
{
    private $_prop = 0;

    public function setProp(string $value): void
    {
        $this->_prop = (int) $value;
    }
}
