<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereAllWithFindAllRector\Source;

class PlainOrderFinder
{
    public static function find(): self
    {
        return new self();
    }

    public function where(array $condition): self
    {
        return $this;
    }

    /**
     * @return self[]
     */
    public function all(): array
    {
        return [];
    }
}
