<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

class PlainClass
{
    public const EXIT_CODE_NORMAL = 0;

    public function run()
    {
        return self::EXIT_CODE_NORMAL;
    }
}
