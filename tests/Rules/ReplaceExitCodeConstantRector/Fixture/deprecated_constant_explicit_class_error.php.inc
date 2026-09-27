<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Source\ProcessController;

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

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExitCodeConstantRector\Source\ProcessController;

class SomeService
{
    public function run(): int
    {
        return \yii\console\ExitCode::UNSPECIFIED_ERROR;
    }
}
