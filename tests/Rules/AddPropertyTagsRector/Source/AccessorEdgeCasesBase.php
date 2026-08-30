<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source;

use yii\base\BaseObject;

class AccessorEdgeCasesBase extends BaseObject
{
    public static function getStaticValue(): int
    {
        return 0;
    }

    public function getRequiredParamValue(int $index): int
    {
        return $index;
    }

    public function setNoParamValue(): void {}

    protected function getProtectedValue(): int
    {
        return 0;
    }
}
