<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use yii\web\Controller;
use yii\web\Response;

class SiteController extends Controller
{
    public function actionIndex(Response $response)
    {
        return $response->response;
    }
}
