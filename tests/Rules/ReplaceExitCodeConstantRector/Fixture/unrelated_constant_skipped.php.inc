<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    private const SOME_OTHER_CONSTANT = 5;

    public function actionRun()
    {
        return self::SOME_OTHER_CONSTANT;
    }
}
