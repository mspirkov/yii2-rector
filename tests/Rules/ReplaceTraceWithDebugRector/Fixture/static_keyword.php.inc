<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

class SomeLogger extends \yii\BaseYii
{
    public static function log(string $message): void
    {
        static::trace($message);
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceTraceWithDebugRector\Fixture;

class SomeLogger extends \yii\BaseYii
{
    public static function log(string $message): void
    {
        static::debug($message);
    }
}
