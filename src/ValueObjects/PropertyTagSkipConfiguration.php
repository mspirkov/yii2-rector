<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\ValueObjects;

use InvalidArgumentException;

final class PropertyTagSkipConfiguration
{
    /** @var list<string> */
    private array $fullySkippedClasses;

    /** @var array<string, list<string>> */
    private array $skippedPropertiesByClass;

    /**
     * @param list<string> $fullySkippedClasses
     * @param array<string, list<string>> $skippedPropertiesByClass
     */
    private function __construct(array $fullySkippedClasses, array $skippedPropertiesByClass)
    {
        $this->fullySkippedClasses = $fullySkippedClasses;
        $this->skippedPropertiesByClass = $skippedPropertiesByClass;
    }

    public static function init(): self
    {
        return new self([], []);
    }

    /**
     * @param mixed[] $configuration
     */
    public static function fromConfiguration(array $configuration, string $configurationKey): self
    {
        $skippedClasses = $configuration[$configurationKey] ?? [];

        if (!is_array($skippedClasses)) {
            throw new InvalidArgumentException(sprintf(
                'The "%s" configuration must be an array, got "%s".',
                $configurationKey,
                gettype($skippedClasses)
            ));
        }

        $fullySkippedClasses = [];
        $skippedPropertiesByClass = [];

        foreach ($skippedClasses as $key => $value) {
            if (is_int($key)) {
                if (!is_string($value)) {
                    throw new InvalidArgumentException(sprintf(
                        'Numeric keys of "%s" must map to a class-string, got "%s".',
                        $configurationKey,
                        gettype($value)
                    ));
                }

                $fullySkippedClasses[] = $value;

                continue;
            }

            if (!is_array($value)) {
                throw new InvalidArgumentException(sprintf(
                    'The "%s" entry for class "%s" must be a list of property names, got "%s".',
                    $configurationKey,
                    $key,
                    gettype($value)
                ));
            }

            foreach ($value as $propertyName) {
                if (!is_string($propertyName)) {
                    throw new InvalidArgumentException(sprintf(
                        'The "%s" property list for class "%s" must contain only strings, got "%s".',
                        $configurationKey,
                        $key,
                        gettype($propertyName)
                    ));
                }
            }

            $skippedPropertiesByClass[$key] = array_values($value);
        }

        return new self($fullySkippedClasses, $skippedPropertiesByClass);
    }

    public function isClassSkipped(string $className): bool
    {
        return in_array($className, $this->fullySkippedClasses, true);
    }

    /**
     * @return list<string>
     */
    public function getSkippedProperties(string $className): array
    {
        return $this->skippedPropertiesByClass[$className] ?? [];
    }

    public function isPropertySkipped(string $className, string $propertyName): bool
    {
        return in_array($propertyName, $this->getSkippedProperties($className), true);
    }
}
