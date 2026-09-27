<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

class PlainClass
{
    public const EXIT_CODE_ERROR = 1;

    public function run()
    {
        return self::EXIT_CODE_ERROR;
    }
}
