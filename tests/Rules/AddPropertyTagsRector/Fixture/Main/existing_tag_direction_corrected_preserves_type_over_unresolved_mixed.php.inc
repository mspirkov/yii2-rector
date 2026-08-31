<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

/**
 * @property Money $custom
 */
class ProductWithDirectionCorrectedAndUntypedGetter extends BaseObject
{
    public function getCustom()
    {
        return Money::find();
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Money;
use yii\base\BaseObject;

/**
 * @property-read Money $custom
 */
class ProductWithDirectionCorrectedAndUntypedGetter extends BaseObject
{
    public function getCustom()
    {
        return Money::find();
    }
}
