<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

abstract class BaseForm extends Model
{
    abstract public function rules(): array;
}
