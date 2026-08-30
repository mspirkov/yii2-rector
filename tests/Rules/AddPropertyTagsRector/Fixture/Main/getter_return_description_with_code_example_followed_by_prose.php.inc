<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

class ProductWithCodeExampleFollowedByProse extends BaseObject
{
    /**
     * @return array a mapping like:
     *
     * ```
     * [
     *     'id' => 1,
     * ]
     * ```
     *
     * An empty array means no mapping
     */
    public function getMapping(): array
    {
        return [];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use yii\base\BaseObject;

/**
 * @property-read array $mapping A mapping like:
 *
 * ```
 * [
 *     'id' => 1,
 * ]
 * ```
 *
 * An empty array means no mapping.
 */
class ProductWithCodeExampleFollowedByProse extends BaseObject
{
    /**
     * @return array a mapping like:
     *
     * ```
     * [
     *     'id' => 1,
     * ]
     * ```
     *
     * An empty array means no mapping
     */
    public function getMapping(): array
    {
        return [];
    }
}
