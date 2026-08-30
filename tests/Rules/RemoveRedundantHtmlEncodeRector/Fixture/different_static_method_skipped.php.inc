<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var string $page */

?>
<span class="page"><?= Html::decode($page) ?></span>
