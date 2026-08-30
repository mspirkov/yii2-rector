<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

class SpeedBase extends BaseObject
{
    public function getSpeed(): int
    {
        return 0;
    }
}
