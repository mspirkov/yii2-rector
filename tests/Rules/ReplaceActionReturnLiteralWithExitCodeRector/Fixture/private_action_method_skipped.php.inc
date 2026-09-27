<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    private function actionRun()
    {
        return 0;
    }
}
