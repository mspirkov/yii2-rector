<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var numeric-string $page */

?>
<span class="page"><?= Html::encode($page, false) ?></span>

-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use yii\helpers\Html;

/** @var numeric-string $page */

?>
<span class="page"><?= $page ?></span>
