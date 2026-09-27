<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use yii\web\Controller;
use yii\web\Request;

class SiteController extends Controller
{
    public function actionIndex(Request $request)
    {
        return $request->request;
    }
}
