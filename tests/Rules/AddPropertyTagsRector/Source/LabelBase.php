<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

/**
 * @property-write string $label
 */
class LabelBase extends BaseObject
{
    public function setLabel(string $label): void {}
}
