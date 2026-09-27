<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function actionRun()
    {
        $resolver = static function () {
            return 0;
        };

        return $resolver();
    }
}
