<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var string $message */

?>
<div class="alert"><?= Html::encode($message) ?></div>
