<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\MergeModelRulesRector\Fixture;

class SomeService
{
    public function rules(): array
    {
        return [
            ['login', 'required'],
            ['password', 'required'],
        ];
    }
}
