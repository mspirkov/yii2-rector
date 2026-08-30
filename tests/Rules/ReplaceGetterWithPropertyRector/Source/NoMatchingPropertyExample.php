<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetterWithPropertyRector\Source;

use yii\base\BaseObject;

class NoMatchingPropertyExample extends BaseObject
{
    private $first = 'John';

    private $last = 'Doe';

    public function getFullName(): string
    {
        return $this->first . ' ' . $this->last;
    }
}
