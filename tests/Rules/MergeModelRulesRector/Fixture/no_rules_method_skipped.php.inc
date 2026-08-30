<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class EmptyForm extends Model
{
    public function attributeLabels(): array
    {
        return [];
    }
}
