<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

class ProductWithMultiLineSourceDescription extends BaseObject
{
    /**
     * @return string Formats the product for display, handling null gracefully by falling back to
     * the default catalog label when nothing is set.
     */
    public function getLabel(): string
    {
        return 'Widget';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

/**
 * @property-read string $label Formats
 * the product for display, handling null
 * gracefully by falling back to the
 * default catalog label when nothing is
 * set.
 */
class ProductWithMultiLineSourceDescription extends BaseObject
{
    /**
     * @return string Formats the product for display, handling null gracefully by falling back to
     * the default catalog label when nothing is set.
     */
    public function getLabel(): string
    {
        return 'Widget';
    }
}
