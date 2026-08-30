<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class StatusForm extends Model
{
    public function rules(): array
    {
        return [
            ['status', 'required'],
            ['status', 'required'],
        ];
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

class StatusForm extends Model
{
    public function rules(): array
    {
        return [
            ['status', 'required'],
        ];
    }
}
