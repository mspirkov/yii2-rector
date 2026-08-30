<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class ContactForm extends Model
{
    public function rules(): array
    {
        return [
            ['name', 'required'],
            ['email', 'required'],
            ['subject', 'required'],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class ContactForm extends Model
{
    public function rules(): array
    {
        return [
            [['name', 'email', 'subject'], 'required'],
        ];
    }
}
