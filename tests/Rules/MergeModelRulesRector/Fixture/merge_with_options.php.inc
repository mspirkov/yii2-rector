<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class ProfileForm extends Model
{
    public function rules(): array
    {
        return [
            ['firstName', 'string', 'max' => 255],
            ['lastName', 'string', 'max' => 255],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class ProfileForm extends Model
{
    public function rules(): array
    {
        return [
            [['firstName', 'lastName'], 'string', 'max' => 255],
        ];
    }
}
