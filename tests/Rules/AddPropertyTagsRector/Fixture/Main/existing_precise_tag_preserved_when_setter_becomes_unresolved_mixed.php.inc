<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write string $data
 */
class ProductWithUntypedSetterAndPreciseExistingWriteTag extends BaseObject
{
    private $data;

    public function setData($data): void
    {
        $this->data = $data;
    }
}
