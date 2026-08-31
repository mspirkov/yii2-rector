<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Analyzers;

use PHPStan\Reflection\ClassReflection;
use ReflectionMethod;

final class BaseObjectAnalyzer
{
    private ParamAnalyzer $paramAnalyzer;

    public function __construct(ParamAnalyzer $paramAnalyzer)
    {
        $this->paramAnalyzer = $paramAnalyzer;
    }

    public function findPropertyUsableMethod(ClassReflection $classReflection, string $propertyName, bool $isGetter): ?ReflectionMethod
    {
        $methodName = ($isGetter ? 'get' : 'set') . ucfirst($propertyName);

        $nativeReflection = $classReflection->getNativeReflection();
        if (!$nativeReflection->hasMethod($methodName)) {
            return null;
        }

        $reflectionMethod = $nativeReflection->getMethod($methodName);
        if (!$reflectionMethod->isPublic() || $reflectionMethod->isStatic()) {
            return null;
        }

        $parameters = $reflectionMethod->getParameters();

        if ($isGetter) {
            return $this->paramAnalyzer->isAllNativeParamsOptional($parameters) ? $reflectionMethod : null;
        }

        if ($parameters === [] || !$this->paramAnalyzer->isAllNativeParamsOptionalAfterFirst($parameters)) {
            return null;
        }

        return $reflectionMethod;
    }

    public function hasPropertyUsableMethod(ClassReflection $classReflection, string $propertyName, bool $isGetter): bool
    {
        return $this->findPropertyUsableMethod($classReflection, $propertyName, $isGetter) !== null;
    }

    public function hasConflictingNativeProperty(ClassReflection $classReflection, string $propertyName): bool
    {
        return $classReflection->hasNativeProperty($propertyName)
            && $classReflection->getNativeProperty($propertyName)->isPublic();
    }
}
