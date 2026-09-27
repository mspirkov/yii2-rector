<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
}

class SomeService
{
    public function run(): int
    {
        return ProcessController::EXIT_CODE_ERROR;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use yii\console\Controller;

class ProcessController extends Controller
{
}

class SomeService
{
    public function run(): int
    {
        return \yii\console\ExitCode::UNSPECIFIED_ERROR;
    }
}
