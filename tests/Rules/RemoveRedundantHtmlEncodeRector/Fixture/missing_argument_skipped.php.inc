<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

?>
<span><?= Html::encode() ?></span>
