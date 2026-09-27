<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceGetHasChangedWithIsChangedRector\Source;

class NonDependencyChecker
{
    /**
     * @param mixed $cache
     */
    public function getHasChanged($cache): bool
    {
        return false;
    }
}
