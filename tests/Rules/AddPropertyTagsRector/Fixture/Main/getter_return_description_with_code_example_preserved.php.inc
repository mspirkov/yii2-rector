<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithCodeExampleReturnDescription extends BaseObject
{
    /**
     * @return array a mapping. The array should look like the following:
     *
     * ```
     * [
     *     'id' => 1,
     *     'title' => 'Widget',
     * ]
     * ```
     */
    public function getAttributes(): array
    {
        return [];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read array $attributes A mapping. The array should look like the following:
 *
 * ```
 * [
 *     'id' => 1,
 *     'title' => 'Widget',
 * ]
 * ```
 *
 */
class ProductWithCodeExampleReturnDescription extends BaseObject
{
    /**
     * @return array a mapping. The array should look like the following:
     *
     * ```
     * [
     *     'id' => 1,
     *     'title' => 'Widget',
     * ]
     * ```
     */
    public function getAttributes(): array
    {
        return [];
    }
}
