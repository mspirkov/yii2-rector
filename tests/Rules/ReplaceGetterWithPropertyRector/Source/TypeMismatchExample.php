<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read string $prop
 */
class TypeMismatchExample extends BaseObject
{
    private $_prop = 0;

    public function getProp(): int
    {
        return $this->_prop;
    }
}
