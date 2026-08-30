<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\TaskBase;

class FlexiblePriorityTask extends TaskBase
{
    /**
     * @return int|string
     */
    public function getPriority()
    {
        return 'high';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\TaskBase;

/**
 * @property-read int|string $priority
 */
class FlexiblePriorityTask extends TaskBase
{
    /**
     * @return int|string
     */
    public function getPriority()
    {
        return 'high';
    }
}
