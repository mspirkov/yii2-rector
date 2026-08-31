<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use MSpirkov\Yii2\Rector\Analyzers\BaseObjectAnalyzer;
use MSpirkov\Yii2\Rector\Analyzers\ParamAnalyzer;
use MSpirkov\Yii2\Rector\ValueObjects\PropertyTagInsertBeforeConfiguration;
use MSpirkov\Yii2\Rector\ValueObjects\PropertyTagSkipConfiguration;
use MSpirkov\Yii2\Rector\Helpers\StringHelper;
use MSpirkov\Yii2\Rector\Analyzers\TypeAnalyzer;
use MSpirkov\Yii2\Rector\Resolvers\PropertyTagResolver;
use PhpParser\Node;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\Array_;
use PhpParser\Node\Expr\ClassConstFetch;
use PhpParser\Node\Expr\MethodCall;
use PhpParser\Node\Identifier;
use PhpParser\Node\Name;
use PhpParser\Node\NullableType;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Return_;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocChildNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PropertyTagValueNode;
use PHPStan\PhpDocParser\Ast\Type\ArrayTypeNode;
use PHPStan\PhpDocParser\Ast\Type\IdentifierTypeNode;
use PHPStan\PhpDocParser\Ast\Type\NullableTypeNode;
use PHPStan\PhpDocParser\Ast\Type\TypeNode;
use PHPStan\Reflection\ClassReflection;
use PHPStan\Reflection\ParametersAcceptorSelector;
use PHPStan\Reflection\ReflectionProvider;
use PHPStan\Type\ArrayType;
use PHPStan\Type\MixedType;
use PHPStan\Type\ObjectType;
use PHPStan\Type\Type;
use PHPStan\Type\TypeCombinator;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\BetterPhpDocParser\ValueObject\Type\BracketsAwareUnionTypeNode;
use Rector\Comments\NodeDocBlock\DocBlockUpdater;
use Rector\Contract\Rector\ConfigurableRectorInterface;
use Rector\NodeTypeResolver\Node\AttributeKey;
use Rector\PhpParser\AstResolver;
use Rector\Rector\AbstractRector;
use Rector\StaticTypeMapper\StaticTypeMapper;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\base\BaseObject;
use yii\db\ActiveQuery;
use yii\db\BaseActiveRecord;

/**
 * @phpstan-type PropertyTypeInfo array{typeNode: TypeNode, type: Type, description: string}
 */
final class AddPropertyTagsRector extends AbstractRector implements ConfigurableRectorInterface, DocumentedRuleInterface
{
    /**
     * @internal
     */
    public const SKIPPED_CLASSES = 'skippedClasses';

    /**
     * @internal
     */
    public const INSERT_BEFORE_TAGS = 'insertBeforeTags';

    private const GETTER_METHOD_NAME_PATTERN = '/^get(?<property>[A-Z]\w*)$/';

    private const SETTER_METHOD_NAME_PATTERN = '/^set(?<property>[A-Z]\w*)$/';

    /** @var list<string> */
    private const RELATION_METHOD_NAMES = ['hasOne', 'hasMany'];

    private ReflectionProvider $reflectionProvider;

    private PhpDocInfoFactory $phpDocInfoFactory;

    private DocBlockUpdater $docBlockUpdater;

    private StaticTypeMapper $staticTypeMapper;

    private PropertyTagResolver $propertyTagResolver;

    private TypeAnalyzer $typeAnalyzer;

    private ParamAnalyzer $paramAnalyzer;

    private BaseObjectAnalyzer $baseObjectAnalyzer;

    private AstResolver $astResolver;

    private PropertyTagSkipConfiguration $skippedClassesConfiguration;

    private PropertyTagInsertBeforeConfiguration $insertBeforeTagsConfiguration;

    public function __construct(
        ReflectionProvider $reflectionProvider,
        PhpDocInfoFactory $phpDocInfoFactory,
        DocBlockUpdater $docBlockUpdater,
        StaticTypeMapper $staticTypeMapper,
        PropertyTagResolver $propertyTagResolver,
        TypeAnalyzer $typeAnalyzer,
        ParamAnalyzer $paramAnalyzer,
        BaseObjectAnalyzer $baseObjectAnalyzer,
        AstResolver $astResolver
    ) {
        $this->reflectionProvider = $reflectionProvider;
        $this->phpDocInfoFactory = $phpDocInfoFactory;
        $this->docBlockUpdater = $docBlockUpdater;
        $this->staticTypeMapper = $staticTypeMapper;
        $this->propertyTagResolver = $propertyTagResolver;
        $this->typeAnalyzer = $typeAnalyzer;
        $this->paramAnalyzer = $paramAnalyzer;
        $this->baseObjectAnalyzer = $baseObjectAnalyzer;
        $this->astResolver = $astResolver;
        $this->skippedClassesConfiguration = PropertyTagSkipConfiguration::init();
        $this->insertBeforeTagsConfiguration = PropertyTagInsertBeforeConfiguration::init();
    }

    /**
     * @param mixed[] $configuration
     */
    public function configure(array $configuration): void
    {
        $this->skippedClassesConfiguration = PropertyTagSkipConfiguration::fromConfiguration(
            $configuration,
            self::SKIPPED_CLASSES
        );

        $this->insertBeforeTagsConfiguration = PropertyTagInsertBeforeConfiguration::fromConfiguration(
            $configuration,
            self::INSERT_BEFORE_TAGS
        );
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Add (or correct) `@property`/`@property-read`/`@property-write` tags on a '
            . '`yii\base\BaseObject` subclass, based on its own `getXxx()`/`setXxx()` method pairs '
            . 'and ActiveRecord relation getters (`hasOne()`/`hasMany()`). Configurable via '
            . '`skippedClasses` — a plain array value (e.g. `\'App\\Foo\'`) fully skips a class, while '
            . 'a string key mapped to a list of property names (e.g. `\'App\\Bar\' => [\'name\']`) '
            . 'skips only those properties — and `insertBeforeTags`, a list of PHPDoc tag names '
            . '(defaulting to `[\'@author\', \'@since\', \'@mixin\']`) before which newly added '
            . '`@property*` tags are inserted',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class Product extends BaseObject
                        {
                            private string $_name;

                            private int $_price;

                            private float $_discount;

                            /**
                             * @return string The product name.
                             */
                            public function getName(): string
                            {
                                return $this->_name;
                            }

                            /**
                             * @param string $name The product name.
                             */
                            public function setName(string $name): void
                            {
                                $this->_name = $name;
                            }

                            public function getPrice(): int
                            {
                                return $this->_price;
                            }

                            public function setDiscount(float $discount): void
                            {
                                $this->_discount = $discount;
                            }
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        /**
                         * @property string $name The product name.
                         * @property-read int $price
                         * @property-write float $discount
                         */
                        class Product extends BaseObject
                        {
                            private string $_name;

                            private int $_price;

                            private float $_discount;

                            /**
                             * @return string The product name.
                             */
                            public function getName(): string
                            {
                                return $this->_name;
                            }

                            /**
                             * @param string $name The product name.
                             */
                            public function setName(string $name): void
                            {
                                $this->_name = $name;
                            }

                            public function getPrice(): int
                            {
                                return $this->_price;
                            }

                            public function setDiscount(float $discount): void
                            {
                                $this->_discount = $discount;
                            }
                        }
                        CODE_SAMPLE
                ),
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class Order extends ActiveRecord
                        {
                            public function getCustomer(): ActiveQuery
                            {
                                return $this->hasOne(Customer::class, ['id' => 'customer_id']);
                            }

                            public function getItems(): ActiveQuery
                            {
                                return $this->hasMany(OrderItem::class, ['order_id' => 'id']);
                            }
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        /**
                         * @property-read Customer|null $customer
                         * @property-read OrderItem[] $items
                         */
                        class Order extends ActiveRecord
                        {
                            public function getCustomer(): ActiveQuery
                            {
                                return $this->hasOne(Customer::class, ['id' => 'customer_id']);
                            }

                            public function getItems(): ActiveQuery
                            {
                                return $this->hasMany(OrderItem::class, ['order_id' => 'id']);
                            }
                        }
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [Class_::class];
    }

    /**
     * @param Class_ $node
     */
    public function refactor(Node $node): ?Node
    {
        if ($node->isAnonymous()) {
            return null;
        }

        if (!$this->isObjectType($node, new ObjectType(BaseObject::class))) {
            return null;
        }

        /** @var string $className */
        $className = $this->getName($node);

        if ($this->skippedClassesConfiguration->isClassSkipped($className)) {
            return null;
        }

        $classReflection = $this->reflectionProvider->getClass($className);
        $desiredTagsByProperty = $this->collectDesiredPropertyTags($node, $classReflection);

        foreach ($this->skippedClassesConfiguration->getSkippedProperties($className) as $skippedProperty) {
            unset($desiredTagsByProperty[$skippedProperty]);
        }

        if ($desiredTagsByProperty === []) {
            return null;
        }

        $classPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($node);
        $hasChanged = false;

        foreach ($desiredTagsByProperty as $propertyName => $desiredTags) {
            if ($this->baseObjectAnalyzer->hasConflictingNativeProperty($classReflection, $propertyName)) {
                continue;
            }

            if ($this->applyPropertyTag($classPhpDocInfo, $node, $propertyName, $desiredTags)) {
                $hasChanged = true;
            }
        }

        if (!$hasChanged) {
            return null;
        }

        $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);

        return $node;
    }

    /**
     * @return array<string, array<string, PropertyTypeInfo>>
     */
    private function collectDesiredPropertyTags(Class_ $class, ClassReflection $classReflection): array
    {
        $getters = [];
        $setters = [];

        foreach ($class->getMethods() as $classMethod) {
            if ($classMethod->isStatic() || !$classMethod->isPublic()) {
                continue;
            }

            $methodName = $this->getName($classMethod);
            $getterProperty = $this->resolveGetterPropertyName($methodName);

            if ($getterProperty !== null && $this->paramAnalyzer->isAllParamsOptional($classMethod->getParams())) {
                $getter = $this->resolveGetterType($classMethod, $classReflection, $methodName, $getterProperty);
                if ($getter !== null) {
                    if ($getter['description'] === '') {
                        $getter['description'] = $this->resolveAncestorDescription($classReflection, $methodName, true);
                    }

                    $getters[$getterProperty] = $getter;
                }

                continue;
            }

            $setterProperty = $this->resolveSetterPropertyName($methodName);

            if (
                $setterProperty !== null
                && $classMethod->getParams() !== []
                && $this->paramAnalyzer->isAllParamsOptionalAfterFirst($classMethod->getParams())
            ) {
                $setter = $this->resolveFirstParamType($classMethod, $classReflection, $methodName);
                if ($setter !== null) {
                    if ($setter['description'] === '') {
                        $setter['description'] = $this->resolveAncestorDescription($classReflection, $methodName, false);
                    }

                    $setters[$setterProperty] = $setter;
                }
            }
        }

        foreach (array_keys($getters) as $propertyName) {
            if (isset($setters[$propertyName])) {
                continue;
            }

            $inheritedSetter = $this->resolveInheritedAccessorType($classReflection, $propertyName, false);
            if ($inheritedSetter !== null) {
                $setters[$propertyName] = $inheritedSetter;
            }
        }

        foreach (array_keys($setters) as $propertyName) {
            if (isset($getters[$propertyName])) {
                continue;
            }

            $inheritedGetter = $this->resolveInheritedAccessorType($classReflection, $propertyName, true);
            if ($inheritedGetter !== null) {
                $getters[$propertyName] = $inheritedGetter;
            }
        }

        $desiredTagsByProperty = [];

        foreach ($getters as $propertyName => $getter) {
            $setter = $setters[$propertyName] ?? null;
            $desiredTagsByProperty[$propertyName] = $this->buildDesiredTagsForGetter($getter, $setter);
        }

        foreach ($setters as $propertyName => $setter) {
            if (isset($desiredTagsByProperty[$propertyName])) {
                continue;
            }

            $desiredTagsByProperty[$propertyName] = [
                '@property-write' => $this->finalizeTag($setter),
            ];
        }

        foreach (array_keys($desiredTagsByProperty) as $propertyName) {
            if ($this->isRedundantWithAncestor($classReflection, $propertyName, $desiredTagsByProperty[$propertyName])) {
                unset($desiredTagsByProperty[$propertyName]);
            }
        }

        return $desiredTagsByProperty;
    }

    /**
     * @return PropertyTypeInfo|null
     */
    private function resolveInheritedAccessorType(ClassReflection $classReflection, string $propertyName, bool $isGetter): ?array
    {
        $reflectionMethod = $this->baseObjectAnalyzer->findPropertyUsableMethod($classReflection, $propertyName, $isGetter);
        if ($reflectionMethod === null) {
            return null;
        }

        $methodName = $reflectionMethod->getName();
        $declaringClassReflection = $this->reflectionProvider->getClass($reflectionMethod->getDeclaringClass()->getName());
        $variant = ParametersAcceptorSelector::combineAcceptors(
            $declaringClassReflection->getNativeMethod($methodName)->getVariants()
        );

        $type = $isGetter ? $variant->getReturnType() : $variant->getParameters()[0]->getType();
        $description = $this->resolveAncestorDescription($classReflection, $methodName, $isGetter);

        return [
            'typeNode' => $this->staticTypeMapper->mapPHPStanTypeToPHPStanPhpDocTypeNode($type),
            'type' => $type,
            'description' => $description,
        ];
    }

    private function resolveAncestorDescription(ClassReflection $classReflection, string $methodName, bool $isGetter): string
    {
        $ancestorClassReflection = $classReflection->getParentClass();

        while (
            $ancestorClassReflection instanceof ClassReflection
            && $ancestorClassReflection->getNativeReflection()->hasMethod($methodName)
        ) {
            $reflectionMethod = $ancestorClassReflection->getNativeReflection()->getMethod($methodName);
            $declaringClassReflection = $this->reflectionProvider->getClass($reflectionMethod->getDeclaringClass()->getName());

            $classMethod = $this->astResolver->resolveClassMethodFromMethodReflection(
                $declaringClassReflection->getNativeMethod($methodName)
            );

            if ($classMethod !== null) {
                $description = $isGetter
                    ? $this->resolveReturnTagDescription($classMethod)
                    : $this->resolveFirstParamDescription($classMethod);

                if ($description !== '') {
                    return $description;
                }
            }

            $ancestorClassReflection = $declaringClassReflection->getParentClass();
        }

        return '';
    }

    private function resolveFirstParamDescription(ClassMethod $classMethod): string
    {
        if ($classMethod->getParams() === []) {
            return '';
        }

        $firstParam = $classMethod->getParams()[0];

        /** @var string $paramName */
        $paramName = $this->getName($firstParam->var);

        $methodPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $paramTagValue = $methodPhpDocInfo->getParamTagValueByName($paramName);

        return $paramTagValue !== null ? $this->normalizeDescription($paramTagValue->description) : '';
    }

    /**
     * @param array<string, PropertyTypeInfo> $desiredTags
     */
    private function isRedundantWithAncestor(ClassReflection $classReflection, string $propertyName, array $desiredTags): bool
    {
        /** @var ClassReflection $parentClass */
        $parentClass = $classReflection->getParentClass();
        $ancestorTag = $this->propertyTagResolver->resolve($parentClass, $propertyName);

        if ($ancestorTag === null) {
            return false;
        }

        $desiredReadableType = null;
        $desiredWritableType = null;

        foreach ($desiredTags as $tagName => $tag) {
            if ($tagName === '@property' || $tagName === '@property-read') {
                $desiredReadableType = $tag['type'];
            }

            if ($tagName === '@property' || $tagName === '@property-write') {
                $desiredWritableType = $tag['type'];
            }
        }

        return $this->typesMatch($desiredReadableType, $ancestorTag->getReadableType())
            && $this->typesMatch($desiredWritableType, $ancestorTag->getWritableType());
    }

    private function typesMatch(?Type $desiredType, ?Type $ancestorType): bool
    {
        if ($desiredType === null || $ancestorType === null) {
            return $desiredType === $ancestorType;
        }

        return $desiredType->equals($ancestorType);
    }

    private function resolveGetterPropertyName(string $methodName): ?string
    {
        if (\preg_match(self::GETTER_METHOD_NAME_PATTERN, $methodName, $matches) !== 1) {
            return null;
        }

        return \lcfirst($matches['property']);
    }

    private function resolveSetterPropertyName(string $methodName): ?string
    {
        if (\preg_match(self::SETTER_METHOD_NAME_PATTERN, $methodName, $matches) !== 1) {
            return null;
        }

        return \lcfirst($matches['property']);
    }

    /**
     * @return PropertyTypeInfo|null
     */
    private function resolveGetterType(
        ClassMethod $classMethod,
        ClassReflection $classReflection,
        string $methodName,
        string $propertyName
    ): ?array {
        $relationType = $this->resolveRelationPropertyType($classMethod, $classReflection, $propertyName);
        if ($relationType !== null) {
            return [
                'typeNode' => $relationType['typeNode'],
                'type' => $relationType['type'],
                'description' => $this->resolveReturnTagDescription($classMethod),
            ];
        }

        $returnType = $this->resolveReturnType($classMethod, $classReflection, $methodName);
        if ($returnType !== null && $this->isActiveRecordActiveQueryGetter($returnType['type'], $classReflection)) {
            return null;
        }

        return $returnType;
    }

    private function isActiveRecordActiveQueryGetter(Type $returnType, ClassReflection $classReflection): bool
    {
        return $classReflection->is(BaseActiveRecord::class)
            && (new ObjectType(ActiveQuery::class))->isSuperTypeOf($returnType)->yes();
    }

    private function resolveReturnTagDescription(ClassMethod $classMethod): string
    {
        $methodPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $returnTagValue = $methodPhpDocInfo->getReturnTagValue();

        return $this->normalizeDescription($returnTagValue !== null ? $returnTagValue->description : '');
    }

    private function normalizeDescription(string $description): string
    {
        $lines = explode("\n", $description);
        $firstLine = array_shift($lines);

        $strippedLines = array_map(
            static fn(string $line): string => (string) preg_replace('/^\s*\*\s?/', '', $line),
            $lines
        );

        return trim(implode("\n", [$firstLine, ...$strippedLines]));
    }

    private function finalizeDescriptionPunctuation(string $description): string
    {
        $body = ucfirst(rtrim($description, "\n"));
        $trailingNewlines = substr($description, strlen($body));

        if (substr($body, -3) !== '```' && !in_array(substr($body, -1), ['.', '!', '?', ':'], true)) {
            $body .= '.';
        }

        return $body . $trailingNewlines;
    }

    private function finalizeDescriptionForTag(string $description): string
    {
        if ($description === '') {
            return $description;
        }

        $description = $this->finalizeDescriptionPunctuation($description);

        if (strpos($description, "\n") !== false) {
            return $this->prefixContinuationLines($description);
        }

        return $description;
    }

    private function prefixContinuationLines(string $description): string
    {
        $lines = explode("\n", $description);
        $firstLine = array_shift($lines);

        $continuationLines = array_map(
            static fn(string $line): string => $line === '' ? ' *' : ' * ' . $line,
            $lines
        );

        return implode("\n", [$firstLine, ...$continuationLines]);
    }

    /**
     * @return array{typeNode: TypeNode, type: Type}|null
     */
    private function resolveRelationPropertyType(
        ClassMethod $classMethod,
        ClassReflection $classReflection,
        string $propertyName
    ): ?array {
        if ($classMethod->stmts === null) {
            return null;
        }

        $relation = $this->findRelationCall($classMethod->stmts);
        if ($relation === null) {
            return null;
        }

        $relatedClass = $this->resolveRelatedClassNameFromCall($relation['call'], $classReflection);
        if ($relatedClass === null) {
            return null;
        }

        $identifierTypeNode = new IdentifierTypeNode($relatedClass['displayName']);
        $objectType = new ObjectType($relatedClass['fqcn']);

        if (!$relation['isMultiple']) {
            if ($this->shouldHasOneRelationBeNullable($relation['call'], $classReflection, $propertyName)) {
                return [
                    'typeNode' => new BracketsAwareUnionTypeNode([$identifierTypeNode, new IdentifierTypeNode('null')]),
                    'type' => TypeCombinator::addNull($objectType),
                ];
            }

            return ['typeNode' => $identifierTypeNode, 'type' => $objectType];
        }

        return [
            'typeNode' => new ArrayTypeNode($identifierTypeNode),
            'type' => new ArrayType(new MixedType(), $objectType),
        ];
    }

    private function shouldHasOneRelationBeNullable(
        MethodCall $methodCall,
        ClassReflection $classReflection,
        string $propertyName
    ): bool {
        if ($this->isRelationNullable($methodCall, $classReflection)) {
            return true;
        }

        $existingPropertyTag = $this->propertyTagResolver->resolve($classReflection, $propertyName);
        if ($existingPropertyTag === null) {
            return true;
        }

        $existingReadableType = $existingPropertyTag->getReadableType();

        return $existingReadableType !== null && TypeCombinator::containsNull($existingReadableType);
    }

    private function isRelationNullable(MethodCall $methodCall, ClassReflection $classReflection): bool
    {
        foreach ($this->resolveLinkAttributeNames($methodCall) as $attributeName) {
            $propertyTag = $this->propertyTagResolver->resolve($classReflection, $attributeName);
            $readableType = $propertyTag !== null ? $propertyTag->getReadableType() : null;

            if ($readableType !== null && TypeCombinator::containsNull($readableType)) {
                return true;
            }
        }

        return false;
    }

    /**
     * @return list<string>
     */
    private function resolveLinkAttributeNames(MethodCall $methodCall): array
    {
        $args = $methodCall->getArgs();
        if (!isset($args[1]) || $args[1]->unpack) {
            return [];
        }

        $linkArgument = $args[1]->value;
        if (!$linkArgument instanceof Array_) {
            return [];
        }

        $attributeNames = [];

        foreach ($linkArgument->items as $item) {
            if (!$item->value instanceof String_) {
                return [];
            }

            $attributeNames[] = $item->value->value;
        }

        return $attributeNames;
    }

    /**
     * @param array<Node\Stmt> $stmts
     *
     * @return array{call: MethodCall, isMultiple: bool}|null
     */
    private function findRelationCall(array $stmts): ?array
    {
        foreach ($stmts as $stmt) {
            if (!$stmt instanceof Return_ || $stmt->expr === null) {
                continue;
            }

            $relation = $this->findRelationCallInExpr($stmt->expr);
            if ($relation !== null) {
                return $relation;
            }
        }

        return null;
    }

    /**
     * @return array{call: MethodCall, isMultiple: bool}|null
     */
    private function findRelationCallInExpr(Expr $expr): ?array
    {
        if (!$expr instanceof MethodCall) {
            return null;
        }

        if (
            $this->isNames($expr->name, self::RELATION_METHOD_NAMES)
            && $this->isObjectType($expr->var, new ObjectType(BaseActiveRecord::class))
        ) {
            return ['call' => $expr, 'isMultiple' => $this->isName($expr->name, 'hasMany')];
        }

        return $this->findRelationCallInExpr($expr->var);
    }

    /**
     * @return array{fqcn: string, displayName: string}|null
     */
    private function resolveRelatedClassNameFromCall(MethodCall $methodCall, ClassReflection $classReflection): ?array
    {
        $args = $methodCall->getArgs();
        if (!isset($args[0]) || $args[0]->unpack) {
            return null;
        }

        $classArgument = $args[0]->value;
        if (!$classArgument instanceof ClassConstFetch || !$this->isName($classArgument->name, 'class')) {
            return null;
        }

        if (!$classArgument->class instanceof Name) {
            return null;
        }

        // "self"/"static" are meaningful `@property` pseudo-types in their own right — keep them
        // as the display text verbatim, but resolve them to the enclosing class for the
        // (comparison-only) PHPStan Type, since ObjectType('self') isn't a real class.
        if ($this->isNames($classArgument->class, ['self', 'static'])) {
            return [
                'fqcn' => $classReflection->getName(),
                'displayName' => $classArgument->class->toString(),
            ];
        }

        // "parent" is left unresolved: unlike self/static, it needs the parent class's own
        // reflection to back the comparison Type, which isn't worth the extra plumbing for what
        // is, in practice, a very rare way to declare an ActiveRecord relation.
        if ($this->isName($classArgument->class, 'parent')) {
            return null;
        }

        $fqcn = $this->getName($classArgument->class);

        return ['fqcn' => $fqcn, 'displayName' => $this->resolveClassDisplayName($classArgument->class)];
    }

    private function resolveClassDisplayName(Node $classNameNode): string
    {
        /** @var Name $originalName */
        $originalName = $classNameNode->getAttribute(AttributeKey::ORIGINAL_NAME);

        return $originalName->toString();
    }

    /**
     * @return PropertyTypeInfo|null
     */
    private function resolveReturnType(ClassMethod $classMethod, ClassReflection $classReflection, string $methodName): ?array
    {
        $methodPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $returnTagValue = $methodPhpDocInfo->getReturnTagValue();

        if ($returnTagValue !== null) {
            if ($this->typeAnalyzer->isConditionalType($returnTagValue->type)) {
                return null;
            }

            $type = $this->staticTypeMapper->mapPHPStanPhpDocTypeNodeToPHPStanType($returnTagValue->type, $classMethod);

            return [
                'typeNode' => $returnTagValue->type,
                'type' => $type,
                'description' => $this->normalizeDescription($returnTagValue->description),
            ];
        }

        $type = ParametersAcceptorSelector::combineAcceptors(
            $classReflection->getNativeMethod($methodName)->getVariants()
        )->getReturnType();

        $typeNode = $this->resolveNativeTypeNode($classMethod->returnType)
            ?? $this->staticTypeMapper->mapPHPStanTypeToPHPStanPhpDocTypeNode($type);

        return ['typeNode' => $typeNode, 'type' => $type, 'description' => ''];
    }

    /**
     * @return PropertyTypeInfo|null
     */
    private function resolveFirstParamType(ClassMethod $classMethod, ClassReflection $classReflection, string $methodName): ?array
    {
        $firstParam = $classMethod->getParams()[0];

        /** @var string $paramName */
        $paramName = $this->getName($firstParam->var);

        $methodPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($classMethod);
        $paramTagValue = $methodPhpDocInfo->getParamTagValueByName($paramName);

        if ($paramTagValue !== null) {
            if ($this->typeAnalyzer->isConditionalType($paramTagValue->type)) {
                return null;
            }

            $type = $this->staticTypeMapper->mapPHPStanPhpDocTypeNodeToPHPStanType($paramTagValue->type, $classMethod);

            return [
                'typeNode' => $paramTagValue->type,
                'type' => $type,
                'description' => $this->normalizeDescription($paramTagValue->description),
            ];
        }

        $parameters = ParametersAcceptorSelector::combineAcceptors(
            $classReflection->getNativeMethod($methodName)->getVariants()
        )->getParameters();

        $type = $parameters[0]->getType();

        $typeNode = $this->resolveNativeTypeNode($firstParam->type)
            ?? $this->staticTypeMapper->mapPHPStanTypeToPHPStanPhpDocTypeNode($type);

        return ['typeNode' => $typeNode, 'type' => $type, 'description' => ''];
    }

    private function resolveNativeTypeNode(?Node $typeNode): ?TypeNode
    {
        if ($typeNode instanceof NullableType) {
            $innerTypeNode = $this->resolveNativeTypeNode($typeNode->type);

            return $innerTypeNode === null ? null : new NullableTypeNode($innerTypeNode);
        }

        if ($typeNode instanceof Identifier) {
            return new IdentifierTypeNode($typeNode->toString());
        }

        if ($typeNode instanceof Name) {
            return new IdentifierTypeNode($this->resolveClassDisplayName($typeNode));
        }

        return null;
    }

    /**
     * @param array<string, PropertyTypeInfo> $desiredTags
     */
    private function applyPropertyTag(
        PhpDocInfo $classPhpDocInfo,
        Node $contextNode,
        string $propertyName,
        array $desiredTags
    ): bool {
        $existingTags = $this->getExistingPropertyTagNodes($classPhpDocInfo, $propertyName);
        $desiredTags = $this->preserveExistingTypesOverUnresolvedMixed($existingTags, $desiredTags, $contextNode);

        if ($this->matchesDesired($existingTags, $desiredTags, $contextNode)) {
            return false;
        }

        $existingTagNodes = array_column($existingTags, 'tagNode');
        $remainingTags = $desiredTags;

        $phpDocNode = $classPhpDocInfo->getPhpDocNode();
        $children = [];
        $insertAt = null;

        foreach ($phpDocNode->children as $child) {
            if ($child instanceof PhpDocTagNode && in_array($child, $existingTagNodes, true)) {
                if (isset($remainingTags[$child->name])) {
                    $remainingTag = $remainingTags[$child->name];
                    $child->value = new PropertyTagValueNode(
                        $remainingTag['typeNode'],
                        '$' . $propertyName,
                        $remainingTag['description']
                    );

                    $children[] = $child;
                    unset($remainingTags[$child->name]);
                }

                $insertAt = count($children);

                continue;
            }

            $children[] = $child;
        }

        $newTagNodes = [];
        foreach ($remainingTags as $tagName => $tag) {
            $newTagNodes[] = new PhpDocTagNode(
                $tagName,
                new PropertyTagValueNode($tag['typeNode'], '$' . $propertyName, $tag['description'])
            );
        }

        array_splice(
            $children,
            $insertAt ?? $this->resolveInsertBeforeConfiguredTagIndex($children) ?? count($children),
            0,
            $newTagNodes
        );

        $phpDocNode->children = $children;

        return true;
    }

    /**
     * @param list<array{tagNode: PhpDocTagNode, value: PropertyTagValueNode}> $existingTags
     * @param array<string, PropertyTypeInfo> $desiredTags
     *
     * @return array<string, PropertyTypeInfo>
     */
    private function preserveExistingTypesOverUnresolvedMixed(array $existingTags, array $desiredTags, Node $contextNode): array
    {
        $existingValueByTagName = [];
        foreach ($existingTags as $existingTag) {
            $existingValueByTagName[$existingTag['tagNode']->name] = $existingTag['value'];
        }

        foreach ($desiredTags as $tagName => $tag) {
            if (!$tag['type'] instanceof MixedType || $tag['type']->isExplicitMixed()) {
                continue;
            }

            $existingValue = $existingValueByTagName[$tagName] ?? null;
            if ($existingValue === null) {
                continue;
            }

            $existingType = $this->staticTypeMapper->mapPHPStanPhpDocTypeNodeToPHPStanType($existingValue->type, $contextNode);
            if ($existingType instanceof MixedType) {
                continue;
            }

            $desiredTags[$tagName] = [
                'typeNode' => $existingValue->type,
                'type' => $existingType,
                'description' => $existingValue->description,
            ];
        }

        return $desiredTags;
    }

    /**
     * @param list<PhpDocChildNode> $children
     */
    private function resolveInsertBeforeConfiguredTagIndex(array $children): ?int
    {
        foreach ($children as $index => $child) {
            if ($child instanceof PhpDocTagNode && $this->insertBeforeTagsConfiguration->containsTagName($child->name)) {
                return $index;
            }
        }

        return null;
    }

    /**
     * @param PropertyTypeInfo $getter
     * @param PropertyTypeInfo|null $setter
     *
     * @return array<string, PropertyTypeInfo>
     */
    private function buildDesiredTagsForGetter(array $getter, ?array $setter): array
    {
        if ($setter === null) {
            return ['@property-read' => $this->finalizeTag($getter)];
        }

        if ($getter['type']->equals($setter['type'])) {
            $description = $getter['description'] !== '' ? $getter['description'] : $setter['description'];
            $tag = ['typeNode' => $getter['typeNode'], 'type' => $getter['type'], 'description' => $description];

            return ['@property' => $this->finalizeTag($tag)];
        }

        return [
            '@property-read' => $this->finalizeTag($getter),
            '@property-write' => $this->finalizeTag($setter),
        ];
    }

    /**
     * @param PropertyTypeInfo $tag
     *
     * @return PropertyTypeInfo
     */
    private function finalizeTag(array $tag): array
    {
        return [
            'typeNode' => $tag['typeNode'],
            'type' => $tag['type'],
            'description' => $this->finalizeDescriptionForTag($tag['description']),
        ];
    }

    /**
     * @return list<array{tagNode: PhpDocTagNode, value: PropertyTagValueNode}>
     */
    private function getExistingPropertyTagNodes(PhpDocInfo $classPhpDocInfo, string $propertyName): array
    {
        $matching = [];

        foreach (['@property', '@property-read', '@property-write'] as $tagName) {
            foreach ($classPhpDocInfo->getTagsByName($tagName) as $phpDocTagNode) {
                if (!$phpDocTagNode->value instanceof PropertyTagValueNode) {
                    continue;
                }

                if (ltrim($phpDocTagNode->value->propertyName, '$') === $propertyName) {
                    $matching[] = ['tagNode' => $phpDocTagNode, 'value' => $phpDocTagNode->value];
                }
            }
        }

        return $matching;
    }

    /**
     * @param list<array{tagNode: PhpDocTagNode, value: PropertyTagValueNode}> $existingTags
     * @param array<string, PropertyTypeInfo> $desiredTags
     */
    private function matchesDesired(array $existingTags, array $desiredTags, Node $contextNode): bool
    {
        if (count($existingTags) !== count($desiredTags)) {
            return false;
        }

        $existingByTagName = [];

        foreach ($existingTags as $existingTag) {
            $existingByTagName[$existingTag['tagNode']->name][] = $existingTag['value'];
        }

        foreach ($desiredTags as $tagName => $tag) {
            if (!isset($existingByTagName[$tagName]) || count($existingByTagName[$tagName]) !== 1) {
                return false;
            }

            $existingValue = $existingByTagName[$tagName][0];
            if (!$this->isDescriptionsEquivalent($existingValue->description, $tag['description'])) {
                return false;
            }

            $existingType = $this->staticTypeMapper->mapPHPStanPhpDocTypeNodeToPHPStanType(
                $existingValue->type,
                $contextNode
            );

            if (!$existingType->equals($tag['type'])) {
                return false;
            }
        }

        return true;
    }

    private function isDescriptionsEquivalent(string $existingDescription, string $desiredDescription): bool
    {
        return StringHelper::collapseWhitespace($existingDescription) === StringHelper::collapseWhitespace($desiredDescription);
    }
}
