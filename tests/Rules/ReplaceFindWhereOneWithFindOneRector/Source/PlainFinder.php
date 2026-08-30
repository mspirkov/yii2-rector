<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\ReplaceFindWhereOneWithFindOneRector\Source;

class PlainFinder
{
    public static function find(): self
    {
        return new self();
    }

    public function where(array $condition): self
    {
        return $this;
    }

    public function one(): ?self
    {
        return null;
    }
}
