<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class RegistrationForm extends Model
{
    public function rules(): array
    {
        return [
            ['login', 'required'],
            ['password', 'required'],
            ['firstName', 'string', 'max' => 255],
            ['lastName', 'string', 'max' => 255],
            ['email', 'email'],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class RegistrationForm extends Model
{
    public function rules(): array
    {
        return [
            [['login', 'password'], 'required'],
            [['firstName', 'lastName'], 'string', 'max' => 255],
            ['email', 'email'],
        ];
    }
}
