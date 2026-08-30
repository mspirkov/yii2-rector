<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    /** @var array<int, string> */
    private $someRule = ['login', 'required'];

    public function rules(): array
    {
        return [
            $this->someRule,
        ];
    }
}
