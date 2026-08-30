<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

class PlainClassWithGetter
{
    public function getName(): string
    {
        return 'name';
    }
}
