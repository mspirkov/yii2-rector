<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use MSpirkov\Yii2\Rector\PropertyTagResolver;
use PhpParser\Node;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Expr\PropertyFetch;
use PHPStan\Reflection\ClassReflection;
use PHPStan\Reflection\ParametersAcceptorSelector;
use PHPStan\Reflection\ReflectionProvider;
use PHPStan\Type\MixedType;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Rector\StaticTypeMapper\Resolver\ClassNameFromObjectTypeResolver;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\base\BaseObject;

final class ReplaceGetterWithPropertyRector extends AbstractRector implements DocumentedRuleInterface
{
    private const GETTER_METHOD_NAME_PATTERN = '/^get(?<property>[A-Z]\w*)$/';

    private ReflectionProvider $reflectionProvider;

    private PropertyTagResolver $propertyTagResolver;

    public function __construct(ReflectionProvider $reflectionProvider, PropertyTagResolver $propertyTagResolver)
    {
        $this->reflectionProvider = $reflectionProvider;
        $this->propertyTagResolver = $propertyTagResolver;
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace a `yii\base\BaseObject` getter call with the equivalent magic-property access, '
                . 'when the property is documented via a class-level `@property` or `@property-read` tag '
                . 'whose type matches the getter\'s return type, and there is no public native property of '
                . 'the same name (which would bypass the getter entirely)',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        /**
                         * @property-read string $prop
                         */
                        class Example extends \yii\base\BaseObject
                        {
                            private string $_prop;

                            public function getProp(): string
                            {
                                return $this->_prop;
                            }
                        }

                        $value = (new Example())->getProp();
                        CODE_SAMPLE,
                    <<<'CODE_SAMPLE'
                        /**
                         * @property-read string $prop
                         */
                        class Example extends \yii\base\BaseObject
                        {
                            private string $_prop;

                            public function getProp(): string
                            {
                                return $this->_prop;
                            }
                        }

                        $value = (new Example())->prop;
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [MethodCall::class];
    }

    /**
     * @param MethodCall $node
     */
    public function refactor(Node $node): ?Node
    {
        if ($node->getArgs() !== []) {
            return null;
        }

        if (!$this->isObjectType($node->var, new ObjectType(BaseObject::class))) {
            return null;
        }

        $methodName = $this->getName($node->name);

        if ($methodName === null) {
            return null;
        }

        $propertyName = $this->resolvePropertyName($methodName);

        if ($propertyName === null) {
            return null;
        }

        $className = ClassNameFromObjectTypeResolver::resolve($this->getType($node->var));

        if ($className === null || !$this->reflectionProvider->hasClass($className)) {
            return null;
        }

        $classReflection = $this->reflectionProvider->getClass($className);

        if (!$this->hasMatchingProperty($classReflection, $propertyName, $methodName)) {
            return null;
        }

        return new PropertyFetch($node->var, $propertyName);
    }

    private function resolvePropertyName(string $methodName): ?string
    {
        if (\preg_match(self::GETTER_METHOD_NAME_PATTERN, $methodName, $matches) !== 1) {
            return null;
        }

        return \lcfirst($matches['property']);
    }

    private function hasMatchingProperty(
        ClassReflection $classReflection,
        string $propertyName,
        string $methodName
    ): bool {
        if (!$classReflection->hasNativeMethod($methodName)) {
            return false;
        }

        if ($classReflection->hasNativeProperty($propertyName) && $classReflection->getNativeProperty(
            $propertyName
        )->isPublic()) {
            return false;
        }

        $propertyTag = $this->propertyTagResolver->resolve($classReflection, $propertyName);

        if ($propertyTag === null || !$propertyTag->isReadable()) {
            return false;
        }

        $propertyType = $propertyTag->getReadableType();
        $returnType = ParametersAcceptorSelector::combineAcceptors(
            $classReflection->getNativeMethod($methodName)->getVariants()
        )->getReturnType();

        if ($propertyType instanceof MixedType || $returnType instanceof MixedType) {
            return false;
        }

        return $propertyType->equals($returnType);
    }
}
