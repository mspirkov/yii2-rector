<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    public function rules(): array
    {
        return [
            ['login', 'required'],
            ['password', 'required'],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class LoginForm extends Model
{
    public function rules(): array
    {
        return [
            [['login', 'password'], 'required'],
        ];
    }
}
