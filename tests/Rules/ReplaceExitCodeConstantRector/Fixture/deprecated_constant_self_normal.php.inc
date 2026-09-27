<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function actionRun()
    {
        return self::EXIT_CODE_NORMAL;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
    public function actionRun()
    {
        return \yii\console\ExitCode::OK;
    }
}
