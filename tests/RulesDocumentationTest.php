<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Tests;

use ReflectionClass;
use Rector\Rector\AbstractRector;
use Rector\Testing\PHPUnit\AbstractLazyTestCase;
use RuntimeException;
use SebastianBergmann\Diff\Differ;
use Symplify\RuleDocGenerator\Contract\CodeSampleInterface;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

final class RulesDocumentationTest extends AbstractLazyTestCase
{
    private const RULES_DIRECTORY = __DIR__ . '/../src/Rules';

    private const RULES_NAMESPACE = 'MSpirkov\\Yii2\\Rector\\Rules\\';

    private const README_PATH = __DIR__ . '/../README.md';

    private const SECTION_START = '<!-- rules-list:start -->';

    private const SECTION_END = '<!-- rules-list:end -->';

    private const TABLE_SECTION_START = '<!-- rules-table:start -->';

    private const TABLE_SECTION_END = '<!-- rules-table:end -->';

    public function testReadmeRulesSectionMatchesRuleDefinitions(): void
    {
        $this->expectNotToPerformAssertions();

        $expectedTable = $this->renderRulesTable();
        $expectedSection = $this->renderRulesSection();

        $readme = (string) file_get_contents(self::README_PATH);
        $actualTable = $this->extractSection($readme, self::TABLE_SECTION_START, self::TABLE_SECTION_END);
        $actualSection = $this->extractSection($readme, self::SECTION_START, self::SECTION_END);

        $readme = $this->replaceSection($readme, self::TABLE_SECTION_START, self::TABLE_SECTION_END, $expectedTable);
        $readme = $this->replaceSection($readme, self::SECTION_START, self::SECTION_END, $expectedSection);
        file_put_contents(self::README_PATH, $readme);

        if ($actualTable !== $expectedTable || $actualSection !== $expectedSection) {
            self::markTestIncomplete(
                'The "Rules" section in README.md was out of date with the rules\' getRuleDefinition() '
                    . 'and has just been regenerated — review the diff and commit it.'
            );
        }
    }

    /**
     * @return list<class-string<AbstractRector>>
     */
    private function discoverRuleClasses(): array
    {
        $files = glob(self::RULES_DIRECTORY . '/*.php');
        if ($files === false) {
            throw new RuntimeException('Failed to scan "' . self::RULES_DIRECTORY . '" for rule classes.');
        }

        $ruleClasses = [];
        foreach ($files as $file) {
            $ruleClass = self::RULES_NAMESPACE . basename($file, '.php');
            if (!is_a($ruleClass, AbstractRector::class, true)) {
                throw new RuntimeException(sprintf(
                    '"%s" does not extend "%s".',
                    $ruleClass,
                    AbstractRector::class
                ));
            }

            $ruleClasses[] = $ruleClass;
        }

        sort($ruleClasses);

        return $ruleClasses;
    }

    private function renderRulesTable(): string
    {
        $rows = array_map(
            fn(string $ruleClass): string => $this->renderTableRow($this->make($ruleClass)),
            $this->discoverRuleClasses()
        );

        return self::TABLE_SECTION_START . "\n\n"
            . "| Rule | Description |\n"
            . "| --- | --- |\n"
            . implode("\n", $rows) . "\n\n" . self::TABLE_SECTION_END;
    }

    private function renderTableRow(AbstractRector $rule): string
    {
        $shortName = (new ReflectionClass($rule))->getShortName();

        return sprintf(
            '| [%s](#%s) | %s |',
            $shortName,
            strtolower($shortName),
            $this->extractFirstSentence($this->getRuleDefinition($rule)->getDescription())
        );
    }

    private function extractFirstSentence(string $description): string
    {
        $position = strpos($description, '. ');

        return $position === false ? $description : substr($description, 0, $position + 1);
    }

    private function renderRulesSection(): string
    {
        $ruleBlocks = array_map(
            fn(string $ruleClass): string => $this->renderRule($this->make($ruleClass)),
            $this->discoverRuleClasses()
        );

        return self::SECTION_START . "\n\n" . implode("\n\n", $ruleBlocks) . "\n\n" . self::SECTION_END;
    }

    private function renderRule(AbstractRector $rule): string
    {
        $ruleDefinition = $this->getRuleDefinition($rule);

        $parts = [
            '### ' . (new ReflectionClass($rule))->getShortName(),
            $ruleDefinition->getDescription(),
        ];

        foreach ($ruleDefinition->getCodeSamples() as $codeSample) {
            $parts[] = $this->renderCodeSample($codeSample);
        }

        return implode("\n\n", $parts);
    }

    private function getRuleDefinition(AbstractRector $rule): RuleDefinition
    {
        if (!$rule instanceof DocumentedRuleInterface) {
            throw new RuntimeException(sprintf(
                '"%s" does not implement "%s".',
                get_class($rule),
                DocumentedRuleInterface::class
            ));
        }

        return $rule->getRuleDefinition();
    }

    private function renderCodeSample(CodeSampleInterface $codeSample): string
    {
        $differ = new Differ();

        /** @var array<array{string, int}> */
        $diffEntries = $differ->diffToArray($codeSample->getBadCode(), $codeSample->getGoodCode());

        $lines = [];

        foreach ($diffEntries as [$line, $type]) {
            if ($type === Differ::ADDED) {
                $prefix = '+';
            } elseif ($type === Differ::REMOVED) {
                $prefix = '-';
            } elseif ($type === Differ::OLD) {
                $prefix = ' ';
            } else {
                continue;
            }

            $lines[] = rtrim($prefix . rtrim($line, "\n"));
        }

        $diff = rtrim(implode("\n", $lines));

        return "```diff\n{$diff}\n```";
    }

    private function extractSection(string $readme, string $sectionStart, string $sectionEnd): ?string
    {
        $start = strpos($readme, $sectionStart);
        $end = strpos($readme, $sectionEnd);

        if ($start === false || $end === false) {
            return null;
        }

        $section = substr($readme, $start, $end + strlen($sectionEnd) - $start) . '';

        return $section !== '' ? $section : null;
    }

    private function replaceSection(string $readme, string $sectionStart, string $sectionEnd, string $newSection): string
    {
        $currentSection = $this->extractSection($readme, $sectionStart, $sectionEnd);
        if ($currentSection === null) {
            throw new RuntimeException(sprintf(
                'README.md is missing the "%s" / "%s" markers.',
                $sectionStart,
                $sectionEnd
            ));
        }

        return str_replace($currentSection, $newSection, $readme);
    }
}
