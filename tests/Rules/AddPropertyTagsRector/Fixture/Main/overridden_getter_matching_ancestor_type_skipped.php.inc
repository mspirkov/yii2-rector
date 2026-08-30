<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\TaskBase;

class UrgentTask extends TaskBase
{
    /**
     * @return int
     */
    public function getPriority()
    {
        return 1;
    }
}
