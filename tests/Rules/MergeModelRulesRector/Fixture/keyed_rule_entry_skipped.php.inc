<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    public function rules(): array
    {
        return [
            'main' => ['login', 'required'],
        ];
    }
}
