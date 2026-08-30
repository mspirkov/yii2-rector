<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use MSpirkov\Yii2\Rector\PropertyTagResolver;
use PhpParser\Node;
use PhpParser\Node\Expr\Assign;
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

final class ReplaceSetterWithPropertyRector extends AbstractRector implements DocumentedRuleInterface
{
    private const SETTER_METHOD_NAME_PATTERN = '/^set(?<property>[A-Z]\w*)$/';

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
            'Replace a `yii\base\BaseObject` setter call with the equivalent magic-property assignment, '
                . 'when the property is documented via a class-level `@property` or `@property-write` tag '
                . 'whose type matches the setter\'s parameter type, and there is no public native property '
                . 'of the same name (which would bypass the setter entirely)',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        /**
                         * @property-write string $prop
                         */
                        class Example extends \yii\base\BaseObject
                        {
                            private string $_prop;

                            public function setProp(string $value): void
                            {
                                $this->_prop = $value;
                            }
                        }

                        (new Example())->setProp('value');
                        CODE_SAMPLE,
                    <<<'CODE_SAMPLE'
                        /**
                         * @property-write string $prop
                         */
                        class Example extends \yii\base\BaseObject
                        {
                            private string $_prop;

                            public function setProp(string $value): void
                            {
                                $this->_prop = $value;
                            }
                        }

                        (new Example())->prop = 'value';
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
        if (\count($node->getArgs()) !== 1) {
            return null;
        }

        $arg = $node->getArgs()[0];

        if ($arg->unpack) {
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

        return new Assign(new PropertyFetch($node->var, $propertyName), $arg->value);
    }

    private function resolvePropertyName(string $methodName): ?string
    {
        if (\preg_match(self::SETTER_METHOD_NAME_PATTERN, $methodName, $matches) !== 1) {
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

        if ($propertyTag === null || !$propertyTag->isWritable()) {
            return false;
        }

        $parameters = ParametersAcceptorSelector::combineAcceptors(
            $classReflection->getNativeMethod($methodName)->getVariants()
        )->getParameters();

        if ($parameters === []) {
            return false;
        }

        $propertyType = $propertyTag->getWritableType();
        $paramType = $parameters[0]->getType();

        if ($propertyType instanceof MixedType || $paramType instanceof MixedType) {
            return false;
        }

        return $propertyType->equals($paramType);
    }
}
