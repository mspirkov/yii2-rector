<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var int $stock */

?>
<span class="stock"><?= Html::encode($stock) ?></span>
