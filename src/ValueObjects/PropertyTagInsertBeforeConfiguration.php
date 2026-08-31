<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\ValueObjects;

use InvalidArgumentException;

final class PropertyTagInsertBeforeConfiguration
{
    /** @var list<string> */
    private const DEFAULT_TAG_NAMES = ['@author', '@since', '@mixin'];

    /** @var list<string> */
    private array $tagNames;

    /**
     * @param list<string> $tagNames
     */
    private function __construct(array $tagNames)
    {
        $this->tagNames = $tagNames;
    }

    public static function init(): self
    {
        return new self(self::DEFAULT_TAG_NAMES);
    }

    /**
     * @param mixed[] $configuration
     */
    public static function fromConfiguration(array $configuration, string $configurationKey): self
    {
        $tagNames = $configuration[$configurationKey] ?? self::DEFAULT_TAG_NAMES;

        if (!is_array($tagNames)) {
            throw new InvalidArgumentException(sprintf(
                'The "%s" configuration must be an array, got "%s".',
                $configurationKey,
                gettype($tagNames)
            ));
        }

        foreach ($tagNames as $tagName) {
            if (!is_string($tagName)) {
                throw new InvalidArgumentException(sprintf(
                    'The "%s" configuration must be a list of PHPDoc tag names, got "%s".',
                    $configurationKey,
                    gettype($tagName)
                ));
            }
        }

        return new self(array_values($tagNames));
    }

    public function containsTagName(string $tagName): bool
    {
        return in_array($tagName, $this->tagNames, true);
    }
}
