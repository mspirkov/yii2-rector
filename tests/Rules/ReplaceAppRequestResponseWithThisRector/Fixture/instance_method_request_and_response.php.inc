<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Controller;
use yii\web\Response;

class SiteController extends Controller
{
    public function actionIndex()
    {
        $ip = Yii::$app->request->getUserIP();
        Yii::$app->response->format = Response::FORMAT_JSON;
    }
}

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Controller;
use yii\web\Response;

class SiteController extends Controller
{
    public function actionIndex()
    {
        $ip = $this->request->getUserIP();
        $this->response->format = Response::FORMAT_JSON;
    }
}
