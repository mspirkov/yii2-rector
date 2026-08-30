<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceSetterWithPropertyRector\Source\SpreadArgumentExample;

class SomeService
{
    /**
     * @param array<string> $args
     */
    public function run(SpreadArgumentExample $example, array $args): void
    {
        $example->setProp(...$args);
    }
}
