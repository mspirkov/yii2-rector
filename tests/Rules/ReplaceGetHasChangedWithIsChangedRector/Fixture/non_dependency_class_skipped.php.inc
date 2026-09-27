<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Fixture;

use MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Source\NonDependencyChecker;

class SomeService
{
    public function hasChanged(NonDependencyChecker $checker): bool
    {
        return $checker->getHasChanged(null);
    }
}
