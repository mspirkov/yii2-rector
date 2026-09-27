<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

class PlainController
{
    public function actionRun()
    {
        return 0;
    }
}
