<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Response;

class SomeService
{
    public function setJsonFormat()
    {
        Yii::$app->response->format = Response::FORMAT_JSON;
    }
}
