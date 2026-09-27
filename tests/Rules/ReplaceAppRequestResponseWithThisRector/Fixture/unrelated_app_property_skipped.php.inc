<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Controller;

class SiteController extends Controller
{
    public function actionIndex()
    {
        return Yii::$app->cache;
    }
}
