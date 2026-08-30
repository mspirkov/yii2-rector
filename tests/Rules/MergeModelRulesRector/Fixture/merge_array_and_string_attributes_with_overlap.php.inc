<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class SignupForm extends Model
{
    public function rules(): array
    {
        return [
            [['login', 'email'], 'required'],
            ['email', 'required'],
            ['password', 'required'],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class SignupForm extends Model
{
    public function rules(): array
    {
        return [
            [['login', 'email', 'password'], 'required'],
        ];
    }
}
