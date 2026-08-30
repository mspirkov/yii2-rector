<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

class ColorBase extends BaseObject
{
    public function setColor(string $color): void {}
}
