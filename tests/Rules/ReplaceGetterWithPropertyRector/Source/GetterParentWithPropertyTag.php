<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read string $parentProp
 */
class GetterParentWithPropertyTag extends BaseObject
{
    private $_parentProp = '';

    public function getParentProp(): string
    {
        return $this->_parentProp;
    }
}
