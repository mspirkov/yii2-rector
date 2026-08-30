# yii2-rector

A [Rector](https://github.com/rectorphp/rector) rule set for automated upgrades/refactors of
Yii2 (`yiisoft/yii2`) codebases. It ships as a `rector-extension` composer package: consumers
require it and pull in `Yii2SetList::MAIN` (or individual rule classes) from their own
`rector.php`.

- PHP support: `>=7.4` (this repo's own dev toolchain currently runs on PHP 7.4.33 — don't
  assume PHP 8 syntax/features are available when writing rule code or tests).
- Namespace root: `MSpirkov\Yii2\Rector\` → `src/`, `MSpirkov\Yii2\Rector\Tests\` → `tests/`
  (PSR-4, see `composer.json`).

## Project structure

```text
src/
  Rules/                      One Rector rule class per file, e.g. FooBarRector.php
  Yii2SetList.php             Public entry point: const MAIN points at config/sets/main.php
config/
  sets/main.php                $rectorConfig->rules([...]) — every shipped rule is registered here
tests/
  bootstrap.php                Loads the rector/rector preload (see gotcha #7), vendor/autoload.php,
                                and yii2's Yii.php for PHPUnit
  RulesDocumentationTest.php   Regenerates README.md's "Rules" section from every rule's
                                getRuleDefinition() — see "README.md is generated" below
  Rules/<RuleName>/
    <RuleName>Test.php          extends Rector\Testing\PHPUnit\AbstractRectorTestCase
    Config/configured_rule.php  Minimal RectorConfig that registers only the rule under test
    Fixture/*.php.inc           Before/after code samples (see "Writing tests" below)
    Source/*.php                Shared fixture-scaffolding classes, when a rule needs them
rector.php                     This repo's OWN self-check config (generic core rule sets,
                                not this package's own rules — see "Self-linting" below)
phpstan.dist.neon              level: max + several strict rule packs, analyses src/ + tests/
.php-cs-fixer.dist.php         Code style
README.md                      Has a machine-generated "Rules" section — never hand-edit it
```

## Adding a new rule — step by step

1. **Create the rule class** in `src/Rules/<Name>Rector.php`, namespace `MSpirkov\Yii2\Rector\Rules`,
   `final class ... extends Rector\Rector\AbstractRector implements DocumentedRuleInterface`.
   Minimum shape:

   ```php
   final class FooRector extends AbstractRector implements DocumentedRuleInterface
   {
       public function getRuleDefinition(): RuleDefinition
       {
           return new RuleDefinition('...', [new CodeSample('<before>', '<after>')]);
       }

       public function getNodeTypes(): array
       {
           return [StaticCall::class]; // the PhpParser node type(s) you want to visit
       }

       /** @param StaticCall $node */
       public function refactor(Node $node): ?Node
       {
           // no instanceof narrowing needed — see gotcha #2 below
           // ... return null for "no change", or the replacement/mutated Node
       }
   }
   ```

   `use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;` and
   `use Symplify\RuleDocGenerator\ValueObject\{RuleDefinition, CodeSample\CodeSample};` for the
   definition. These classes aren't in this repo's own `composer.json` — they're loaded lazily
   through `rector/rector`'s own internal autoloader the moment any `Rector\...` class is
   referenced, which is why every existing rule file `use`s an `AbstractRector`/`Rector\...`
   symbol before anything Symplify-namespaced. **`implements DocumentedRuleInterface` is required**,
   not just convention — `AbstractRector` itself doesn't declare `getRuleDefinition()`, and
   `tests/RulesDocumentationTest.php` (see below) needs the interface to call it type-safely.

2. **Register it** in `config/sets/main.php`'s `$rectorConfig->rules([...])` array so it's part
   of `Yii2SetList::MAIN`.

3. **Add tests** under `tests/Rules/<Name>Rector/` — see "Writing tests" below.

4. **Verify** with the full local pipeline (all must be clean before calling a rule done):

   ```bash
   php -d memory_limit=512M ./vendor/bin/phpunit --testsuite Tests
   php ./vendor/bin/phpstan analyse --no-progress
   php ./vendor/bin/php-cs-fixer check --diff      # or `fix` to auto-apply
   php ./vendor/bin/rector process --dry-run        # this repo's own self-check
   ```

   These map to the composer scripts `phpstan`, `lint:check`/`lint:fix`, `rector:check`/`rector:fix`
   (there's no `test` script defined yet — invoke phpunit directly as above).

5. **Line/method/class coverage on every new rule must be 100%** (this box has `ext-xdebug`
   installed but coverage is off by default — needs `XDEBUG_MODE=coverage` for that one
   invocation, otherwise PHPUnit silently skips collection with a warning). See "Closing coverage
   gaps" below — fixtures alone don't reach every line.

## Writing tests

Follow the standard `rector/rector` fixture-test convention:

- `tests/Rules/<Name>Rector/<Name>RectorTest.php` extends `AbstractRectorTestCase`, implements
  `provideConfigFilePath(): string` (points at `Config/configured_rule.php`), and a `test()`
  method fed by a data provider that yields fixture file paths via
  `self::yieldFilesFromDirectory(__DIR__ . '/Fixture')`.
- **Use the classic `@dataProvider` docblock annotation, not the `#[DataProvider]` attribute.**
  This repo's dev dependency is PHPUnit `^9.6` (attributes need PHPUnit 10+); on PHP 7.4 the
  attribute syntax is silently swallowed as a `#`-comment, so the provider just never runs and
  the test silently exercises zero fixtures. Always check `./vendor/bin/phpunit --version` if
  unsure.
- `tests/Rules/<Name>Rector/Config/configured_rule.php` is a `RectorConfig` that registers
  *only* the rule under test via `$rectorConfig->rule(<Name>Rector::class);` — keep it minimal,
  don't reuse the full `main.php` set.
- `Fixture/*.php.inc` files hold one scenario each: content before `-----` is the input, content
  after is the expected output. **Omit the `-----` separator entirely to assert "no change"** —
  useful for documenting guard clauses / cases the rule intentionally must not touch.
- Fixtures use the `.php.inc` extension (not `.php`) on purpose: this repo's own `rector.php`
  and `.php-cs-fixer.dist.php` only scan `*.php` files, so fixture "before" snippets containing
  the deprecated patterns you're testing for never get mangled by this project's own tooling.
- **Every fixture's PHP snippet must declare a real namespace — never rely on the global
  namespace.** The first statement after `<?php` (in both the before and after half, when a
  `-----` separator is present) must be
  `namespace MSpirkov\Yii2\Rector\Tests\Rules\<Name>Rector\Fixture;`, matching the rule under
  test. This is what makes it safe for fixtures/rules to reuse a short class name like
  `SomeService` or `Customer`: two classes with the same short name but different namespaces are
  simply different classes, so there's no risk of the PHPStan-reflection-cache collision that a
  same-name class in the *global* namespace could previously cause across different rules'
  `Fixture/` directories. The one legitimate exception is a fixture whose entire point IS to
  exercise namespace-qualified-class handling (e.g.
  `ReplaceClassnameWithClassRector`'s `namespaced_class_name.php.inc`,
  which deliberately uses `namespace App;`) — that fixture's namespace choice is itself part of
  what's under test, so leave it alone. Watch for namespace-sensitive output: a rule that emits
  a fully-qualified class name (e.g. via `NodeFactory::createClassConstFetch()`, see gotcha #5)
  will render the fixture's own namespace in the "after" half — run the fixture test and read
  the actual output it reports rather than hand-writing the expected FQCN from memory.
- It's normal and safe to reuse the same fixture class *name* (e.g. `SomeService`) across
  different fixture files in the same rule's `Fixture/` directory when the class's body is
  itself the code under test and legitimately varies per fixture (each file is analysed with its
  own fresh PHPStan scope — no cross-fixture leakage). That's typically the "consumer" class
  containing the actual before/after expression, so it belongs inline in the fixture.
- **Any class/interface/trait in a fixture that is not itself part of the before/after diff is
  scaffolding, and belongs in `tests/Rules/<Name>Rector/Source/<ClassName>.php`** (namespaced
  `MSpirkov\Yii2\Rector\Tests\Rules\<Name>Rector\Source`), `use`-imported into the fixture
  instead of declared inline — this applies even when the class is only used by a single
  fixture, not just when it's duplicated across many. The test for "is this scaffolding" is
  simple: if the class's own body is byte-identical between the "before" and "after" half of a
  `-----` fixture (or, for a no-`-----` skip fixture, isn't the thing whose shape the guard
  clause is reacting to), it never changes — it only exists to give the real "consumer" code
  (typically a `SomeService` class, or an `InheritedPropertyTagExample`-style class *referenced*
  by the consumer) something concrete to call a getter/setter/`::find()`/etc. on. Cross-references
  between scaffolding classes in the same rule (a subclass extending another Source class, a
  class implementing a Source interface, `use`ing a Source trait) resolve automatically with no
  additional `use` statements, since every Source class for one rule shares that one `...\Source`
  namespace — PHP resolves same-namespace class names directly. This needs no special
  test-harness wiring either (no `AbstractRectorTestCase::doTestFile(...,
  includeFixtureDirectoryAsSource: true)`) — `tests/bootstrap.php` already loads Composer's
  autoloader, and both Rector's node-type resolver and PHPStan's reflection provider resolve a
  properly PSR-4-namespaced `Source/` class through it exactly like any other class.
  `phpstan.dist.neon`'s `tests/*/Source/*` entry under `excludePaths` already covers this nested
  per-rule layout (the `*` spans multiple path segments), so `Source/` classes are exempt from
  `level: max` strict analysis; `rector.php`'s own `withSkip([...])` has a matching
  `tests/*/*/Source/*` entry so this repo's self-lint doesn't touch them either (verified: without
  it, generic sets like `CODE_QUALITY` do flag them). They're still checked by
  `.php-cs-fixer.dist.php` though (its own `tests/Rules/Source` exclude entry is a literal,
  non-nested path that predates this per-rule layout and doesn't match it — harmless, since
  `Source/` classes are normal PHP and should stay style-consistent with everything else, e.g.
  cs-fixer will happily convert an inline `extends \yii\base\BaseObject` to a `use` import).
  The one thing that must stay inline in the fixture itself is a class whose *own* body IS the
  code under test — the "consumer" class containing the before/after expression, or (for
  `self::`/`static::`/`parent::`-forwarding rules) the model class whose method body contains the
  forwarding call being rewritten in place; extracting either of those to `Source/` would hide
  the actual diff.
- If a rule needs to type-check against a *real* yii2 class (e.g. `yii\base\BaseObject`,
  `yii\db\ActiveRecordInterface`), no stub is needed at all, `Source/` or otherwise —
  `yiisoft/yii2` is a `require` (not `require-dev`) dependency, so PHPStan's reflection provider
  resolves it for every fixture automatically. `Source/` is only for classes this project itself
  authors as reusable fixture scaffolding.

## README.md is generated — never hand-edit the "Rules" section

`tests/RulesDocumentationTest.php` scans `src/Rules/*.php`, instantiates every rule class, and
renders each one's `getRuleDefinition()` (description + a real unified diff of its code sample,
via `sebastian/diff`'s `Differ`/`DiffOnlyOutputBuilder` — already a transitive PHPUnit dependency,
no new `composer.json` entry needed) into the block between the `<!-- rules-list:start -->` /
`<!-- rules-list:end -->` markers in `README.md`.

**The test *always* rewrites that section on every run, then asserts the freshly-generated content
equals what was there before the write.** So it never needs an opt-in flag to refresh itself — but
it does mean: if you change a rule's `getRuleDefinition()` (or add/
remove a rule) and don't re-run the suite, `git status`/the next CI run will show README.md as
dirty, which is the point — the test run itself is what keeps the docs honest, and it fails on any
run where it had to change something, forcing you to review and commit the diff rather than let it
drift silently.

This is also how `getRuleDefinition()` gets its required 100% test coverage — see below.

## Closing coverage gaps

**Every rule must reach 100% line/method/class coverage — this is a hard requirement, not a
nice-to-have.** Check with:

```bash
XDEBUG_MODE=coverage php -d memory_limit=512M ./vendor/bin/phpunit --testsuite Tests --coverage-text
```

Fixture-driven `doTestFile()` runs alone don't get there, because `getRuleDefinition()` never
executes through the normal Rector traversal — it's only called by Rector's own doc-generator/
CLI listing, never by `doTestFile()`. This is covered centrally, for free, by
`tests/RulesDocumentationTest.php` (see above) instantiating every rule and calling it — **no
per-rule `testRuleDefinitionIsDocumented()`-style test needed**, and none should be added; it
would just duplicate what the documentation test already exercises.

(There used to be a second gap here: a defensive `if (!$node instanceof <Type>) { return null; }`
narrowing at the top of `refactor()`, covered by a dedicated per-rule unit test calling
`refactor()` directly with an unrelated node. Since `refactor()` is now narrowed via a `@param`
docblock instead of a runtime `instanceof` check — see gotcha #2 — that branch no longer exists,
so there's nothing left to cover this way; don't add it back.)

Every guard clause in `refactor()` (skip conditions for things the rule must *not* touch) should
be covered by a dedicated no-`-----` "skipped" fixture — that exercises the real traversal path
and doubles as documentation of the guard's intent. See `ReplaceClassnameWithClassRector`'s
`Fixture/*_skipped.php.inc` files for six worked examples (forwarding `self`/`parent` calls, a
dynamic/non-literal class expression, extra arguments, an unrelated method name, and an unrelated
class).

## Gotchas learned the hard way

1. **PHP 7.4 is real, not just a `composer.json` floor.** The CLI that actually runs this
   project's tests is 7.4.33. Anything PHP 8-only (attributes, enums, named-arg-only syntax
   quirks, etc.) will misbehave silently rather than fail loudly — verify against the real
   `php -v` / `./vendor/bin/phpunit --version` when in doubt.

2. **Narrow `refactor(Node $node)`'s param via a `@param SpecificNode $node` docblock, not a
   runtime `instanceof` check.** `getNodeTypes()` already guarantees the framework never calls
   `refactor()` with anything else, so the `instanceof` was purely defensive. The docblock does
   trip `phpstan-strict-rules`: with `treatPhpDocTypesAsCertain: true` (the default here), PHPStan
   treats the docblock as the *real* native type, which then reads as a Liskov/contravariance
   violation against `RectorInterface::refactor(Node $node)` (`method.childParameterType`). That's
   expected — `phpstan.dist.neon` has a project-wide `ignoreErrors` entry (scoped to
   `src/Rules/*.php`, with a TODO explaining why) for exactly this identifier, tracking
   <https://github.com/rectorphp/rector-src/pull/8330> which will make it unnecessary once
   released. Don't add the `instanceof` back to work around it.

3. **`getNodeTypes()` needs no `@return` docblock at all.** `phpstan.dist.neon` carries a
   project-wide `ignoreErrors` entry (scoped to `src/Rules/*.php`) for
   `shipmonk.returnListNotUsed` — `RectorInterface::getNodeTypes()` is documented upstream as
   `@return array<class-string<Node>>`, so shipmonk always flags a rule's implementation as "you
   could narrow this to `list`" even though it already returns one. Same
   <https://github.com/rectorphp/rector-src/pull/8330> tracking as gotcha #2 above; don't re-add
   the `@return list<class-string<Node>>` docblock to silence it locally.

4. **`AbstractRector::getName()` has a conditional PHPDoc return type** (`@return ($node is Name
   ? string : ...)`, see `vendor/rector/rector/src/Rector/AbstractRector.php`). Once you've
   narrowed a node to `Name` (e.g. via `instanceof Name`), PHPStan knows `getName()` on it can't
   return `null` — a defensive `if ($name === null)` check after that point is flagged as
   `identical.alwaysFalse`. Don't add it; trust the narrowed type.

5. **`NodeFactory::createClassConstFetch()` always fully-qualifies plain class names** (renders
   as `\Foo::class`) **unless the *consuming* RectorConfig calls `->withImportNames()`** — and
   the special names `self`/`parent`/`static` are passed through as-is (`static::class`, not
   `\static::class`). Since fixture test configs (`Config/configured_rule.php`) deliberately stay
   minimal and don't enable import names, expect the leading backslash in fixture "after" content
   for any transform that emits an explicit class name. This project's own `rector.php` *does*
   call `->withImportNames()`, so real usage against this repo's own `src/`/`tests/` would import
   it — that's a property of the consumer config, not the rule.

6. **Late static binding matters for anything touching `self::`/`static::`/`parent::` static
   calls.** `self::` and `parent::` are *forwarding* calls (they propagate the caller's late
   static binding), while an explicit class name (`Foo::bar()`) is *non-forwarding* (resets LSB
   to `Foo`), and `static::` is always forwarding. This means e.g. `self::className()` and
   `parent::className()` are **not** generally equivalent to `self::class`/`parent::class` when
   the surrounding class is subclassed — only `static::className()` and explicit
   `SomeClass::className()` are safe to rewrite unconditionally. Any rule rewriting a static
   method call into a compile-time class-name construct needs to reason about this before
   touching `self::`/`parent::` call sites (see `ReplaceClassnameWithClassRector` for a worked
   example, and its `self_keyword_skipped.php.inc` / `parent_keyword_skipped.php.inc` fixtures).

7. **Running the full suite with `XDEBUG_MODE=coverage` can fatal with "Cannot declare class
   PhpParser\Node\UseItem, because the name is already in use"** — `phpunit/php-code-coverage`
   (via `sebastian/complexity`/`sebastian/lines-of-code`, used to compute complexity/LOC metrics
   for the coverage report) pulls in its *own* top-level `nikic/php-parser` install, which
   collides with the separate, unprefixed copy `rector/rector` bundles internally (nikic/php-parser
   is deliberately left unprefixed by Rector's build so rule code can `use PhpParser\Node\...`
   directly, unlike its other internal dependencies). `rector/rector` ships a fix for exactly this
   (`vendor/rector/rector/preload.php`, which `require_once`s its bundled copy's classes first so
   they always win the race) but only auto-applies it for PHPUnit 12+; this repo is pinned to
   PHPUnit `^9.6`. `tests/bootstrap.php` therefore `require`s that `preload.php` itself,
   unconditionally, before `vendor/autoload.php`. Don't remove it — without it, coverage runs are
   flaky-fatal depending on random test execution order (`executionOrder="random"` in
   `phpunit.xml.dist`), since which copy "wins" depends on load timing.

8. **Avoid passing variables by reference in any form — `foreach ($x as &$y)`, a `function
   f(&$x)` parameter, or `$a =& $b`.** There's essentially always a by-value alternative: build a
   new array (`array_map()` for a straight value transform, or a plain `foreach` appending into a
   fresh array when the mapping isn't 1:1) instead of mutating in place via `&$y`; return a new
   value instead of writing into a `&$param`. References make data flow implicit and are easy to
   get subtly wrong (the classic `unset($y)` footgun after a by-reference `foreach`, or a
   reference that outlives the scope you meant it for) — by-value code makes the transform's
   input/output shape explicit and is easier to reason about and review.

## Self-linting (`rector.php` at the repo root)

This is **not** where this package's own rules get dogfooded — `rector.php` runs generic
`rector/rector` core sets (`CODE_QUALITY`, `DEAD_CODE`, `PRIVATIZATION`, `TYPE_DECLARATION`, plus
`withPhp74Sets()`) over this repo's own `src/` and `tests/` to keep the maintainer codebase
itself clean. `Fixture/*.php.inc` files are immune since they aren't `*.php`; `Source/*.php`
files (see "Writing tests" above) *are* real PHP, but `rector.php`'s own `withSkip([...])` array
explicitly skips `tests/*/*/Source/*` (verified: without that entry, generic sets like
`CODE_QUALITY`/`Instanceof_\FlipNegatedTernaryInstanceofRector` do flag them) — `Source/` classes
are pure fixture scaffolding, not code this project ships, so they're not worth self-linting.
`phpstan.dist.neon`'s `excludePaths` and `.php-cs-fixer.dist.php`'s `Finder::exclude()` skip
`Source/`/`Fixture/` too, for their own respective checks — see "Writing tests" for those exact
patterns (note `.php-cs-fixer.dist.php`'s `tests/Rules/Source` entry is a literal, non-nested
path left over from an earlier, never-adopted flat-directory idea, so it does *not* actually
match this per-rule-nested layout; `Source/*.php` files are therefore still checked by cs-fixer,
which is fine since they're normal PHP and should stay style-consistent with everything else).
