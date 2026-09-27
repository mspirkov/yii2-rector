<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceAppRequestResponseWithThisRector\Fixture;

use Yii;
use yii\web\Controller;
use yii\web\Response;

class SiteController extends Controller
{
    public function actionIndex()
    {
        $setJsonFormat = function () {
            Yii::$app->response->format = Response::FORMAT_JSON;
        };

        $setJsonFormat();
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
        $setJsonFormat = function () {
            $this->response->format = Response::FORMAT_JSON;
        };

        $setJsonFormat();
    }
}
