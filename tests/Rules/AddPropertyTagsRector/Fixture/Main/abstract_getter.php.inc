<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

abstract class ProductWithAbstractGetter extends BaseObject
{
    abstract public function getName(): string;
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read string $name
 */
abstract class ProductWithAbstractGetter extends BaseObject
{
    abstract public function getName(): string;
}
