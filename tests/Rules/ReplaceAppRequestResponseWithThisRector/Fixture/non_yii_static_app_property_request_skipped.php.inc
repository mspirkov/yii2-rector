<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Source\NotYii;
use yii\web\Controller;

class SiteController extends Controller
{
    public function actionIndex()
    {
        return NotYii::$app->request;
    }
}
