<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source;

use yii\base\BaseObject;

class NoMatchingSetterPropertyExample extends BaseObject
{
    private $first = 'John';

    private $last = 'Doe';

    public function setFullName(string $value): void
    {
        [$this->first, $this->last] = \explode(' ', $value, 2);
    }
}
