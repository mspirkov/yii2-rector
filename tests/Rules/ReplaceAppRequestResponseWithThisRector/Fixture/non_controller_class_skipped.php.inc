<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;

class SomeService
{
    public function resolveIp()
    {
        return Yii::$app->request->getUserIP();
    }
}
