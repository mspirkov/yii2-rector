<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

class SomeService
{
    public function run(): void
    {
        \Yii::trace('Some message');
        \Yii::trace(['data' => 1], __METHOD__);
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

class SomeService
{
    public function run(): void
    {
        \Yii::debug('Some message');
        \Yii::debug(['data' => 1], __METHOD__);
    }
}
