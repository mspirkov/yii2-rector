<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-write string $prop
 */
class NoParameterSetterExample extends BaseObject
{
    protected string $prop = '';

    public function setProp(): void
    {
        $this->prop = 'fixed';
    }
}
