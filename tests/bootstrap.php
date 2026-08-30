<?php

declare(strict_types=1);

$rootDir = dirname(__DIR__);

// Preload rector/rector's bundled nikic/php-parser and phpstan/phpdoc-parser classes first, so
// they win over this project's own (independently installed, e.g. via phpunit/php-code-coverage)
// copies of the same packages. Without this, code-coverage collection can trigger a
// "Cannot declare class ..., because the name is already in use" fatal from the two copies racing.
require "{$rootDir}/vendor/rector/rector/preload.php";

require "{$rootDir}/vendor/autoload.php";
require "{$rootDir}/vendor/yiisoft/yii2/Yii.php";
