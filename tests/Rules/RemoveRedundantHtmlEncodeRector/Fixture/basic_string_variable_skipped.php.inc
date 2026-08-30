<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var string $title */

?>
<h1><?= Html::encode($title) ?></h1>
