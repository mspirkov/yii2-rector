<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function actionRun(bool $allowed)
    {
        if (!$allowed) {
            return 1;
        }

        return 0;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceActionReturnLiteralWithExitCodeRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function actionRun(bool $allowed)
    {
        if (!$allowed) {
            return \yii\console\ExitCode::UNSPECIFIED_ERROR;
        }

        return \yii\console\ExitCode::OK;
    }
}
