<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

class DescribedSetterBase extends BaseObject
{
    /**
     * @param string $label The new display label.
     */
    public function setLabel(string $label): void {}
}
