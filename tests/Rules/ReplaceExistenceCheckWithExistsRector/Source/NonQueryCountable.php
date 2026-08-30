<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceExistenceCheckWithExistsRector\Source;

final class NonQueryCountable
{
    public function count(): int
    {
        return 0;
    }

    /**
     * @return mixed
     */
    public function one()
    {
        return null;
    }
}
