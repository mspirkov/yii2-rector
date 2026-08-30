<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector;

use PHPStan\PhpDoc\Tag\PropertyTag;
use PHPStan\Reflection\ClassReflection;

final class PropertyTagResolver
{
    public function resolve(ClassReflection $classReflection, string $propertyName): ?PropertyTag
    {
        $propertyTags = $classReflection->getPropertyTags();

        if (isset($propertyTags[$propertyName])) {
            return $propertyTags[$propertyName];
        }

        foreach ($classReflection->getTraits() as $trait) {
            $propertyTag = $this->resolve($trait, $propertyName);

            if ($propertyTag !== null) {
                return $propertyTag;
            }
        }

        $parentClass = $classReflection->getParentClass();

        if ($parentClass !== null) {
            $propertyTag = $this->resolve($parentClass, $propertyName);

            if ($propertyTag !== null) {
                return $propertyTag;
            }
        }

        foreach ($classReflection->getInterfaces() as $interface) {
            $propertyTag = $this->resolve($interface, $propertyName);

            if ($propertyTag !== null) {
                return $propertyTag;
            }
        }

        return null;
    }
}
