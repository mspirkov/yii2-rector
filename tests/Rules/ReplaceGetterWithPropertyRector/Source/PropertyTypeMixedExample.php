<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read mixed $prop
 */
class PropertyTypeMixedExample extends BaseObject
{
    private string $prop;

    public function getProp(): string
    {
        return $this->prop;
    }
}
