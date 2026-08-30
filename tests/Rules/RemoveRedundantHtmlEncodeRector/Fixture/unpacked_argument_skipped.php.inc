<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var array $encodeArgs */

?>
<span><?= Html::encode(...$encodeArgs) ?></span>
