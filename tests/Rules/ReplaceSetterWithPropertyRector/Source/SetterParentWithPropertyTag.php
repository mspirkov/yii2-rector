<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write string $parentProp
 */
class SetterParentWithPropertyTag extends BaseObject
{
    private $_parentProp = '';

    public function setParentProp(string $value): void
    {
        $this->_parentProp = $value;
    }
}
