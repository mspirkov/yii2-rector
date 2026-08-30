<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read string $prop
 */
class ReturnTypeMixedExample extends BaseObject
{
    private $prop;

    /**
     * @return mixed
     */
    public function getProp()
    {
        return $this->prop;
    }
}
