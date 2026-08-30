<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

/**
 * @property-read int $priority
 */
class TaskBase extends BaseObject
{
    /**
     * @return int
     */
    public function getPriority()
    {
        return 0;
    }
}
