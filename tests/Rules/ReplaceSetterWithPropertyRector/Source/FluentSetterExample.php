<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write string $prop
 * @property-write string $otherProp
 */
class FluentSetterExample extends BaseObject
{
    private string $_prop = '';

    private string $_otherProp = '';

    public function setProp(string $value): self
    {
        $this->_prop = $value;

        return $this;
    }

    public function setOtherProp(string $value): self
    {
        $this->_otherProp = $value;

        return $this;
    }
}
