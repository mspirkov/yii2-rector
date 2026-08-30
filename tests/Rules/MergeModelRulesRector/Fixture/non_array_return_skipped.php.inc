<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    public function rules(): array
    {
        return array_merge(parent::rules(), [
            ['login', 'required'],
            ['password', 'required'],
        ]);
    }
}
