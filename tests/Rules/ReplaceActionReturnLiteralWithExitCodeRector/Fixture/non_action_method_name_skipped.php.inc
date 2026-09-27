<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function run()
    {
        return 0;
    }
}
