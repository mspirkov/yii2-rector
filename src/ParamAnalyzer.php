<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector;

use PhpParser\Node\Param;

final class ParamAnalyzer
{
    /**
     * @param array<Param> $params
     */
    public function isAllParamsOptional(array $params): bool
    {
        foreach ($params as $param) {
            if ($param->default === null && !$param->variadic) {
                return false;
            }
        }

        return true;
    }

    /**
     * @param array<Param> $params
     */
    public function isAllParamsOptionalAfterFirst(array $params): bool
    {
        return $this->isAllParamsOptional(array_slice($params, 1));
    }
}
