<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

use yii\base\Model;

function createAnonymousForm()
{
    return new class extends Model {
        public function rules(): array
        {
            return [
                ['login', 'required'],
                ['password', 'required'],
            ];
        }
    };
}
