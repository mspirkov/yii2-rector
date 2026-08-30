<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\LabelBase;

class RenamedWidget extends LabelBase
{
    public function setLabel(string $label): void
    {
    }
}
