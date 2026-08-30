<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    /** @return array<int, array<int, string>> */
    private function extraRules(): array
    {
        return [];
    }

    public function rules(): array
    {
        return [
            ...$this->extraRules(),
        ];
    }
}
