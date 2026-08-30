<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithBulletListParamDescription extends BaseObject
{
    /**
     * @param array|int $value the pagination to be used by this data provider.
     * This can be one of the following:
     *
     * - a configuration array for creating the pagination object.
     * - an instance of Pagination or its subclass
     * - false, if pagination needs to be disabled.
     */
    public function setPagination($value): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-write array|int $pagination The pagination to be used by this data provider. This can be one of
 * the following: - a configuration array for creating the pagination object. - an instance of Pagination or its
 * subclass - false, if pagination needs to be disabled.
 */
class ProductWithBulletListParamDescription extends BaseObject
{
    /**
     * @param array|int $value the pagination to be used by this data provider.
     * This can be one of the following:
     *
     * - a configuration array for creating the pagination object.
     * - an instance of Pagination or its subclass
     * - false, if pagination needs to be disabled.
     */
    public function setPagination($value): void
    {
    }
}
