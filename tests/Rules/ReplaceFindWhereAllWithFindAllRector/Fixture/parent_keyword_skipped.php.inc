<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source\Order;

class PremiumOrder extends Order
{
    /**
     * @return Order[]
     */
    public static function findRegular(): array
    {
        // Not rewritten: Rector resolves "parent" to a union of every ancestor class
        // (Model, Component, BaseObject, ...), not just the immediate parent, so
        // isObjectType() can't confirm it narrowly implements ActiveRecordInterface here.
        return parent::find()->where(['tier' => 'gold'])->all();
    }
}
