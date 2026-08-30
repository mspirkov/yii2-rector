<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\RemoveRedundantHtmlEncodeRector\Source\Encoder;

/** @var string $page */

?>
<span class="page"><?= Encoder::encode($page) ?></span>
