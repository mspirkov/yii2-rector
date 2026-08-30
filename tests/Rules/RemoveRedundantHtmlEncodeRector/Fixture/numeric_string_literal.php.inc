<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var numeric-string $id */

?>
<span class="badge">v<?= Html::encode($id) ?></span>

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var numeric-string $id */

?>
<span class="badge">v<?= $id ?></span>
