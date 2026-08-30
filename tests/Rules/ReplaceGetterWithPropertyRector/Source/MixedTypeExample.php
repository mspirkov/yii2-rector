<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

/**
 * @property-read mixed $prop
 */
class MixedTypeExample extends BaseObject
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
