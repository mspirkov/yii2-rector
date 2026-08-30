<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source\Customer;

class GoldCustomer extends Customer
{
    public static function findRegular(): ?Customer
    {
        // Not rewritten: Rector resolves "parent" to a union of every ancestor class
        // (Model, Component, BaseObject, ...), not just the immediate parent, so
        // isObjectType() can't confirm it narrowly implements ActiveRecordInterface here.
        return parent::find()->where(['tier' => 'gold'])->one();
    }
}
