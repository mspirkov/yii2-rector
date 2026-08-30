<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector;

use PHPStan\PhpDocParser\Ast\Type\ConditionalTypeForParameterNode;
use PHPStan\PhpDocParser\Ast\Type\ConditionalTypeNode;
use PHPStan\PhpDocParser\Ast\Type\TypeNode;

final class TypeAnalyzer
{
    public function isConditionalType(TypeNode $typeNode): bool
    {
        return $typeNode instanceof ConditionalTypeNode || $typeNode instanceof ConditionalTypeForParameterNode;
    }
}
