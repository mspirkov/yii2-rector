<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Controller;
use yii\web\Request;

class SiteController extends Controller
{
    public function actionIndex()
    {
        $definitions = Yii::$container->definitions;
    }
}
