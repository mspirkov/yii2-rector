<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use MSpirkov\Yii2\Rector\Analyzers\BaseObjectAnalyzer;
use MSpirkov\Yii2\Rector\ValueObjects\PropertyTagSkipConfiguration;
use PhpParser\Node;
use PhpParser\Node\Stmt\Class_;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocChildNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PropertyTagValueNode;
use PHPStan\Reflection\ClassReflection;
use PHPStan\Reflection\ReflectionProvider;
use PHPStan\Type\ObjectType;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\Comments\NodeDocBlock\DocBlockUpdater;
use Rector\Contract\Rector\ConfigurableRectorInterface;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\base\BaseObject;
use yii\base\DynamicModel;
use yii\db\BaseActiveRecord;

final class RemoveRedundantPropertyTagsRector extends AbstractRector implements ConfigurableRectorInterface, DocumentedRuleInterface
{
    /**
     * @internal
     */
    public const SKIPPED_CLASSES = 'skippedClasses';

    /** @var list<string> */
    private const PROPERTY_TAG_NAMES = ['@property', '@property-read', '@property-write'];

    private ReflectionProvider $reflectionProvider;

    private PhpDocInfoFactory $phpDocInfoFactory;

    private DocBlockUpdater $docBlockUpdater;

    private BaseObjectAnalyzer $baseObjectAnalyzer;

    private PropertyTagSkipConfiguration $skippedClassesConfiguration;

    public function __construct(
        ReflectionProvider $reflectionProvider,
        PhpDocInfoFactory $phpDocInfoFactory,
        DocBlockUpdater $docBlockUpdater,
        BaseObjectAnalyzer $baseObjectAnalyzer
    ) {
        $this->reflectionProvider = $reflectionProvider;
        $this->phpDocInfoFactory = $phpDocInfoFactory;
        $this->docBlockUpdater = $docBlockUpdater;
        $this->baseObjectAnalyzer = $baseObjectAnalyzer;
        $this->skippedClassesConfiguration = PropertyTagSkipConfiguration::init();
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
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Remove a `@property`/`@property-read`/`@property-write` tag from a `yii\base\BaseObject` '
            . 'subclass when neither a matching public `getXxx()` nor `setXxx()` method exists (own or '
            . 'inherited) — typically left behind after the accessor it documented was renamed or '
            . 'removed. `yii\db\BaseActiveRecord` and `yii\base\DynamicModel` descendants are skipped '
            . 'entirely, since their magic properties aren\'t backed by getter/setter methods. '
            . 'Configurable via `skippedClasses` — a plain array value (e.g. `\'App\\Foo\'`) fully '
            . 'skips a class, while a string key mapped to a list of property names (e.g. '
            . '`\'App\\Bar\' => [\'name\']`) skips only those properties',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        /**
                         * @property string $name
                         * @property-read int $legacyCount
                         */
                        class Product extends BaseObject
                        {
                            public function getName(): string
                            {
                                return 'Widget';
                            }

                            public function setName(string $name): void
                            {
                            }
                        }
                        CODE_SAMPLE,
                    <<<'CODE_SAMPLE'
                        /**
                         * @property string $name
                         */
                        class Product extends BaseObject
                        {
                            public function getName(): string
                            {
                                return 'Widget';
                            }

                            public function setName(string $name): void
                            {
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

        if ($this->isObjectType($node, new ObjectType(BaseActiveRecord::class))) {
            return null;
        }

        if ($this->isObjectType($node, new ObjectType(DynamicModel::class))) {
            return null;
        }

        /** @var string $className */
        $className = $this->getName($node);
        if ($this->skippedClassesConfiguration->isClassSkipped($className)) {
            return null;
        }

        $classReflection = $this->reflectionProvider->getClass($className);
        $classPhpDocInfo = $this->phpDocInfoFactory->createFromNodeOrEmpty($node);
        $phpDocNode = $classPhpDocInfo->getPhpDocNode();

        $redundantTagNodes = $this->resolveRedundantTagNodes($phpDocNode->getTags(), $classReflection, $className);
        if ($redundantTagNodes === []) {
            return null;
        }

        $phpDocNode->children = array_values(array_filter(
            $phpDocNode->children,
            static fn(PhpDocChildNode $child): bool => !in_array($child, $redundantTagNodes, true)
        ));

        $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);

        return $node;
    }

    /**
     * @param PhpDocTagNode[] $tagNodes
     *
     * @return list<PhpDocTagNode>
     */
    private function resolveRedundantTagNodes(array $tagNodes, ClassReflection $classReflection, string $className): array
    {
        $redundantTagNodes = [];

        foreach ($tagNodes as $tagNode) {
            if (!in_array($tagNode->name, self::PROPERTY_TAG_NAMES, true)) {
                continue;
            }

            if (!$tagNode->value instanceof PropertyTagValueNode) {
                continue;
            }

            $propertyName = ltrim($tagNode->value->propertyName, '$');

            if ($this->skippedClassesConfiguration->isPropertySkipped($className, $propertyName)) {
                continue;
            }

            if ($this->baseObjectAnalyzer->hasConflictingNativeProperty($classReflection, $propertyName)) {
                continue;
            }

            if ($this->baseObjectAnalyzer->hasPropertyUsableMethod($classReflection, $propertyName, true)) {
                continue;
            }

            if ($this->baseObjectAnalyzer->hasPropertyUsableMethod($classReflection, $propertyName, false)) {
                continue;
            }

            $redundantTagNodes[] = $tagNode;
        }

        return $redundantTagNodes;
    }
}
