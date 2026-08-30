<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\Category;
use yii\db\ActiveRecord;

/**
 * @property-read Category[] $categories
 * @property-read string $label
 */
class ProductWithExistingCategoriesRelationTag extends ActiveRecord
{
    public function getCategories()
    {
        return $this->hasMany(Category::class, ['product_id' => 'id']);
    }

    public function getLabel(): string
    {
        return '';
    }
}
