<p align="center">
    <a href="https://github.com/yiisoft" target="_blank">
        <img src="https://avatars0.githubusercontent.com/u/993323" height="100px">
    </a>
    <h1 align="center">Yii2 Rector</h1>
</p>

A set of [Rector](https://getrector.com) rules for [Yii2](https://github.com/yiisoft/yii2) projects that I put together for my own day-to-day work.
They make refactoring a Yii2 codebase easier and help keep it cleaner, automating the framework-specific patterns
— magic properties, `ActiveRecord`/`Query` calls, accumulated deprecations — that a generic Rector set has no way
to know about.

[![PHP](https://img.shields.io/badge/%3E%3D7.4-7A86B8.svg?style=for-the-badge&logo=php&logoColor=white&label=PHP)](https://www.php.net/releases/7_4_0.php)
[![Yii2](https://img.shields.io/badge/%3E%3D2.0.53-247BA0.svg?style=for-the-badge&logo=yii&logoColor=white&label=Yii)](https://github.com/yiisoft/yii2/releases/tag/2.0.53)
[![Rector](https://img.shields.io/badge/%3E%3D2.6.0-247BA0.svg?style=for-the-badge&label=Rector)](https://github.com/rectorphp/rector/releases/tag/2.6.0)
[![Total Downloads](https://img.shields.io/packagist/dt/mspirkov/yii2-rector.svg?style=for-the-badge&logo=composer&logoColor=white&label=Downloads)](https://packagist.org/packages/mspirkov/yii2-rector)
[![Tests](https://img.shields.io/github/actions/workflow/status/mspirkov/yii2-rector/ci.yml?branch=main&style=for-the-badge&logo=github&label=Tests)](https://github.com/mspirkov/yii2-rector/actions/workflows/ci.yml)
[![Coverage](https://img.shields.io/codecov/c/github/mspirkov/yii2-rector.svg?branch=main&style=for-the-badge&logo=codecov&logoColor=white&label=Coverage)](https://codecov.io/github/mspirkov/yii2-rector)
[![PHPStan Level Max](https://img.shields.io/badge/Max-7A86B8.svg?style=for-the-badge&label=PHPStan%20Level)](https://github.com/mspirkov/yii2-rector/blob/main/phpstan.dist.neon)

## Support

If you like this project, give it a ⭐ on [GitHub](https://github.com/mspirkov/yii2-rector) — it helps others
discover it.

## Supported extensions

The `ActiveRecord`/`Query` rules aren't limited to the SQL-based `yii\db\ActiveRecord` — they also work with
`ActiveRecord`/`ActiveQuery` classes from popular Yii2 storage extensions such as
[yiisoft/yii2-mongodb](https://github.com/yiisoft/yii2-mongodb) and
[yiisoft/yii2-redis](https://github.com/yiisoft/yii2-redis).

## Installation

> [!IMPORTANT]
>
> It works better with the latest versions of [PHP](https://www.php.net), [Yii2](https://www.yiiframework.com),
> and [Rector](https://getrector.com). The more up‑to‑date the versions, the better the refactoring.

```bash
composer require --dev mspirkov/yii2-rector
```

## Usage

```php
use MSpirkov\Yii2\Rector\Yii2SetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withPaths(...)
    ->withSets([
        Yii2SetList::DEPRECATION,
        Yii2SetList::CODE_QUALITY,
        Yii2SetList::PHPDOC,
    ]);
```

### Sets

Every rule belongs to exactly one set, so you can enable only the kinds of changes you want:

| Set | Description |
| --- | --- |
| `Yii2SetList::DEPRECATION` | Replaces deprecated Yii2 APIs with their current equivalents |
| `Yii2SetList::CODE_QUALITY` | Removes redundant code and simplifies or optimizes framework-specific patterns |
| `Yii2SetList::PHPDOC` | Generates and cleans up PHPDoc annotations, such as `@property` tags |

### Enabling individual rules

Individual rules can be enabled on their own via `->withRules([...])` instead of `->withSets([...])`:

```php
use MSpirkov\Yii2\Rector\Rules\ReplaceClassnameWithClassRector;
use MSpirkov\Yii2\Rector\Rules\ReplaceExistenceCheckWithExistsRector;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withPaths(...)
    ->withRules([
        ReplaceClassnameWithClassRector::class,
        ReplaceExistenceCheckWithExistsRector::class,
    ]);
```

### Skipping rules

Any rule — whether pulled in through a set or added individually — can be turned off entirely via
`->withSkip([...])`:

```php
use MSpirkov\Yii2\Rector\Rules\MergeModelRulesRector;
use MSpirkov\Yii2\Rector\Yii2SetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withPaths(...)
    ->withSets([
        Yii2SetList::DEPRECATION,
        Yii2SetList::CODE_QUALITY,
        Yii2SetList::PHPDOC,
    ])
    ->withSkip([
        MergeModelRulesRector::class,
    ]);
```

Mapping a rule to a list of paths/patterns instead skips it only there, leaving it active everywhere else — handy
for legacy code that isn't ready for a particular rule yet:

```php
    ->withSkip([
        MergeModelRulesRector::class => [
            __DIR__ . '/src/Legacy/*',
        ],
    ]);
```

A plain path/pattern (no rule class key) skips those files from every rule, Yii2-specific or not.

### Configuring a rule

`AddPropertyTagsRector` and `RemoveRedundantPropertyTagsRector` accept a `skippedClasses` option — see the
[rule reference](#rule-reference) below for the exact shape of each — and `AddPropertyTagsRector` additionally
accepts `insertBeforeTags`. Configure them via `->withConfiguredRule()`, using the rule's own constants as keys:

```php
use MSpirkov\Yii2\Rector\Rules\AddPropertyTagsRector;
use MSpirkov\Yii2\Rector\Yii2SetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withPaths(...)
    ->withSets([
        Yii2SetList::DEPRECATION,
        Yii2SetList::CODE_QUALITY,
        Yii2SetList::PHPDOC,
    ])
    ->withConfiguredRule(AddPropertyTagsRector::class, [
        'skippedClasses' => [
            'App\Models\LegacyModel',
            'App\Models\Product' => ['internalNotes'],
        ],
        'insertBeforeTags' => ['@author', '@since'],
    ]);
```

`App\Models\LegacyModel` above is skipped entirely (a plain array value), while only the `internalNotes` property
is skipped on `App\Models\Product` (a class-name key mapped to a list of property names) — every other property
on it is still processed normally.

## Rules at a glance

<!-- rules-table:start -->

| Rule | Description |
| --- | --- |
| [AddPropertyTagsRector](#addpropertytagsrector) | Add (or correct) `@property`/`@property-read`/`@property-write` tags on a `yii\base\BaseObject` subclass, based on its own `getXxx()`/`setXxx()` method pairs and ActiveRecord relation getters (`hasOne()`/`hasMany()`). |
| [MergeModelRulesRector](#mergemodelrulesrector) | Merge `yii\base\Model::rules()` entries that configure the same validator with the same options but a different attribute into one entry, combining their attributes into a single array (an attribute already present in another merged entry is not duplicated). |
| [RemoveRedundantHtmlEncodeRector](#removeredundanthtmlencoderector) | Remove a `yii\helpers\Html::encode()` call whose `$content` argument PHPStan proves is a numeric string — digits only can't contain a character `htmlspecialchars()` would touch, so the call is replaced by its bare `$content` argument (dropping a trailing `$doubleEncode` argument, if present, too). |
| [RemoveRedundantPropertyTagsRector](#removeredundantpropertytagsrector) | Remove a `@property`/`@property-read`/`@property-write` tag from a `yii\base\BaseObject` subclass when neither a matching public `getXxx()` nor `setXxx()` method exists (own or inherited) — typically left behind after the accessor it documented was renamed or removed. |
| [ReplaceActionReturnLiteralWithExitCodeRector](#replaceactionreturnliteralwithexitcoderector) | Replace a literal `return 0;`/`return 1;` in one of a console controller's `action*()` methods with the equivalent `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` constant. |
| [ReplaceAppRequestResponseWithThisRector](#replaceapprequestresponsewiththisrector) | Replace `Yii::$app->request`/`Yii::$app->response` with `$this->request`/`$this->response` inside a `yii\base\Controller` subclass — the controller already exposes the same request/response objects through its own properties |
| [ReplaceCacheMultiMethodAliasesRector](#replacecachemultimethodaliasesrector) | Replace a deprecated `yii\caching\Cache` multi-key method alias — `mget()`, `mset()`, or `madd()` — with its canonical `multiGet()`, `multiSet()`, or `multiAdd()` equivalent |
| [ReplaceClassnameWithClassRector](#replaceclassnamewithclassrector) | Replace the deprecated `yii\base\BaseObject::className()` call with the native `::class` constant. |
| [ReplaceExistenceCheckWithExistsRector](#replaceexistencecheckwithexistsrector) | Replace an existence check on a `yii\db\QueryInterface` result with the cheaper `->exists()` call. |
| [ReplaceExitCodeConstantRector](#replaceexitcodeconstantrector) | Replace a console controller's deprecated `Controller::EXIT_CODE_NORMAL`/`EXIT_CODE_ERROR` constant with the `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` equivalent |
| [ReplaceFindWhereAllWithFindAllRector](#replacefindwhereallwithfindallrector) | Replace `find()->where([...])->all()` on an ActiveRecord class with the equivalent `findAll([...])`. |
| [ReplaceFindWhereOneWithFindOneRector](#replacefindwhereonewithfindonerector) | Replace `find()->where([...])->one()` on an ActiveRecord class with the equivalent `findOne([...])`. |
| [ReplaceGetHasChangedWithIsChangedRector](#replacegethaschangedwithischangedrector) | Replace the deprecated `yii\caching\Dependency::getHasChanged()` call with `isChanged()` |
| [ReplaceGetterWithPropertyRector](#replacegetterwithpropertyrector) | Replace a `yii\base\BaseObject` getter call with the equivalent magic-property access, when the property is documented via a class-level `@property` or `@property-read` tag whose type matches the getter's return type, and there is no public native property of the same name (which would bypass the getter entirely) |
| [ReplaceSetterWithPropertyRector](#replacesetterwithpropertyrector) | Replace a `yii\base\BaseObject` setter call with the equivalent magic-property assignment, when the property is documented via a class-level `@property` or `@property-write` tag whose type matches the setter's parameter type, and there is no public native property of the same name (which would bypass the setter entirely) |
| [ReplaceTraceWithDebugRector](#replacetracewithdebugrector) | Replace the deprecated `Yii::trace()` call with `Yii::debug()` |
| [ReplaceWhereEqualityConditionWithArrayRector](#replacewhereequalityconditionwitharrayrector) | Replace a single-column string `where()`/`andWhere()`/`orWhere()` condition (interpolated or concatenated) with the safer array condition format |

<!-- rules-table:end -->

## Rule reference

<!-- rules-list:start -->

### AddPropertyTagsRector

Add (or correct) `@property`/`@property-read`/`@property-write` tags on a `yii\base\BaseObject` subclass, based on its own `getXxx()`/`setXxx()` method pairs and ActiveRecord relation getters (`hasOne()`/`hasMany()`). A class whose `__get()`/`__set()` is overridden by something other than `yii\base\BaseObject`, `yii\base\Component`, `yii\db\BaseActiveRecord`, or `yii\base\DynamicModel` is skipped entirely, since such magic properties may not correspond to `getXxx()`/`setXxx()` methods. Configurable via `skippedClasses` — a plain array value (e.g. `'App\Foo'`) fully skips a class, while a string key mapped to a list of property names (e.g. `'App\Bar' => ['name']`) skips only those properties — and `insertBeforeTags`, a list of PHPDoc tag names (defaulting to `['@author', '@since', '@mixin']`) before which newly added `@property*` tags are inserted

```diff
+/**
+ * @property string $name The product name.
+ * @property-read int $price
+ * @property-write float $discount
+ */
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
```

```diff
+/**
+ * @property-read Customer|null $customer
+ * @property-read OrderItem[] $items
+ */
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
```

### MergeModelRulesRector

Merge `yii\base\Model::rules()` entries that configure the same validator with the same options but a different attribute into one entry, combining their attributes into a single array (an attribute already present in another merged entry is not duplicated). Two entries only merge when everything after the attribute(s) — the validator and any options — is identical; a `rules()` body that isn't a single `return [...]` of literal rule arrays is left untouched

```diff
 class LoginForm extends Model
 {
     public function rules(): array
     {
         return [
-            ['login', 'required'],
-            ['password', 'required'],
+            [['login', 'password'], 'required'],
         ];
     }
 }
```

### RemoveRedundantHtmlEncodeRector

Remove a `yii\helpers\Html::encode()` call whose `$content` argument PHPStan proves is a numeric string — digits only can't contain a character `htmlspecialchars()` would touch, so the call is replaced by its bare `$content` argument (dropping a trailing `$doubleEncode` argument, if present, too). Any other `$content` is left untouched

```diff
 <?php
 /**
  * @var numeric-string $id
  * @var string $name
  */
 ?>
-<?= Html::encode($id) ?>
+<?= $id ?>
 <?= Html::encode($name) ?>
```

### RemoveRedundantPropertyTagsRector

Remove a `@property`/`@property-read`/`@property-write` tag from a `yii\base\BaseObject` subclass when neither a matching public `getXxx()` nor `setXxx()` method exists (own or inherited) — typically left behind after the accessor it documented was renamed or removed. A tag backed by at least one accessor is left untouched even if it names the wrong direction (e.g. `@property-read` with only a setter) — correcting it to match the accessor that does exist is `AddPropertyTagsRector`'s job, not this rule's, so the two never touch the same tag. A class whose `__get()`/`__set()` isn't the one inherited from `yii\base\BaseObject` or `yii\base\Component` — own override or inherited from some other ancestor, including `yii\db\BaseActiveRecord` and `yii\base\DynamicModel` — is skipped entirely, since its magic properties aren't necessarily backed by getter/setter methods. Configurable via `skippedClasses` — a plain array value (e.g. `'App\Foo'`) fully skips a class, while a string key mapped to a list of property names (e.g. `'App\Bar' => ['name']`) skips only those properties

```diff
 /**
  * @property string $name
- * @property-read int $legacyCount
  */
 class Product extends BaseObject
 {
     private string $_name;

     public function getName(): string
     {
         return $this->_name;
     }

     public function setName(string $name): void
     {
         $this->_name = $name;
     }
 }
```

### ReplaceActionReturnLiteralWithExitCodeRector

Replace a literal `return 0;`/`return 1;` in one of a console controller's `action*()` methods with the equivalent `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` constant. A return inside a closure/arrow function nested in the action method is left untouched, since it isn't the action's own exit code

```diff
 class ProcessController extends Controller
 {
     public function actionRun(bool $allowed)
     {
         if (!$allowed) {
-            return 1;
+            return ExitCode::UNSPECIFIED_ERROR;
         }

-        return 0;
+        return ExitCode::OK;
     }
 }
```

### ReplaceAppRequestResponseWithThisRector

Replace `Yii::$app->request`/`Yii::$app->response` with `$this->request`/`$this->response` inside a `yii\base\Controller` subclass — the controller already exposes the same request/response objects through its own properties

```diff
 class SiteController extends Controller
 {
     public function actionIndex()
     {
-        Yii::$app->response->format = Response::FORMAT_JSON;
+        $this->response->format = Response::FORMAT_JSON;

-        $ip = Yii::$app->request->getUserIP();
+        $ip = $this->request->getUserIP();
     }
 }
```

### ReplaceCacheMultiMethodAliasesRector

Replace a deprecated `yii\caching\Cache` multi-key method alias — `mget()`, `mset()`, or `madd()` — with its canonical `multiGet()`, `multiSet()`, or `multiAdd()` equivalent

```diff
-$cache->mget(['key1', 'key2']);
-$cache->mset(['key1' => 'value1', 'key2' => 'value2']);
-$cache->madd(['key3' => 'value3']);
+$cache->multiGet(['key1', 'key2']);
+$cache->multiSet(['key1' => 'value1', 'key2' => 'value2']);
+$cache->multiAdd(['key3' => 'value3']);
```

### ReplaceClassnameWithClassRector

Replace the deprecated `yii\base\BaseObject::className()` call with the native `::class` constant. `self::className()` and `parent::className()` are left untouched, since both are late-static-binding forwarding calls not generally equivalent to `self::class`/`parent::class` once the class is subclassed — only `static::className()` and an explicit class name are rewritten

```diff
-$class = SomeClass::className();
-$class = static::className();
+$class = SomeClass::class;
+$class = static::class;
```

### ReplaceExistenceCheckWithExistsRector

Replace an existence check on a `yii\db\QueryInterface` result with the cheaper `->exists()` call. Recognises a `->count()` comparison against the boundary literals `0`/`1` (in either operand order) and a strict `->one() !== null` / `->one() === null` check. A check that means "no rows" (e.g. `count() < 1`, `one() === null`) is rewritten to the negated `!exists()`, not `exists()`. Only the boundary comparisons that map unambiguously onto a presence/absence question are recognised — `count() > 1`, for instance, is left untouched

```diff
 public function emailIsTaken(string $email): bool
 {
-    return User::find()->where(['email' => $email])->one() !== null;
+    return User::find()->where(['email' => $email])->exists();
 }

 public function emailIsAvailable(string $email): bool
 {
-    return User::find()->where(['email' => $email])->count() < 1;
+    return !User::find()->where(['email' => $email])->exists();
 }
```

### ReplaceExitCodeConstantRector

Replace a console controller's deprecated `Controller::EXIT_CODE_NORMAL`/`EXIT_CODE_ERROR` constant with the `ExitCode::OK`/`ExitCode::UNSPECIFIED_ERROR` equivalent

```diff
 class ProcessController extends Controller
 {
     public function actionRun()
     {
-        return self::EXIT_CODE_NORMAL;
+        return ExitCode::OK;
     }
 }
```

### ReplaceFindWhereAllWithFindAllRector

Replace `find()->where([...])->all()` on an ActiveRecord class with the equivalent `findAll([...])`. Only fires when the `where()` condition is a literal array keyed entirely by string literals: `findAll()` treats any other condition shape (scalar, list, `Expression`) as a primary key lookup instead of forwarding it to `where()` unchanged, so those shapes are intentionally left untouched.

```diff
-$customers = Customer::find()->where(['status' => 1])->all();
+$customers = Customer::findAll(['status' => 1]);
```

### ReplaceFindWhereOneWithFindOneRector

Replace `find()->where([...])->one()` on an ActiveRecord class with the equivalent `findOne([...])`. Only fires when the `where()` condition is a literal array keyed entirely by string literals: `findOne()` treats any other condition shape (scalar, list, `Expression`) as a primary key lookup instead of forwarding it to `where()` unchanged, so those shapes are intentionally left untouched.

```diff
-$customer = Customer::find()->where(['status' => 1])->one();
+$customer = Customer::findOne(['status' => 1]);
```

### ReplaceGetHasChangedWithIsChangedRector

Replace the deprecated `yii\caching\Dependency::getHasChanged()` call with `isChanged()`

```diff
-$hasChanged = $dependency->getHasChanged($cache);
+$hasChanged = $dependency->isChanged($cache);
```

### ReplaceGetterWithPropertyRector

Replace a `yii\base\BaseObject` getter call with the equivalent magic-property access, when the property is documented via a class-level `@property` or `@property-read` tag whose type matches the getter's return type, and there is no public native property of the same name (which would bypass the getter entirely)

```diff
 /**
  * @property-read string $prop
  */
 class Example extends BaseObject
 {
     private string $_prop;

     public function getProp(): string
     {
         return $this->_prop;
     }
 }

-$value = (new Example())->getProp();
+$value = (new Example())->prop;
```

### ReplaceSetterWithPropertyRector

Replace a `yii\base\BaseObject` setter call with the equivalent magic-property assignment, when the property is documented via a class-level `@property` or `@property-write` tag whose type matches the setter's parameter type, and there is no public native property of the same name (which would bypass the setter entirely)

```diff
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

-(new Example())->setProp('value');
+(new Example())->prop = 'value';
```

### ReplaceTraceWithDebugRector

Replace the deprecated `Yii::trace()` call with `Yii::debug()`

```diff
-Yii::trace('Some message');
-Yii::trace($data, __METHOD__);
+Yii::debug('Some message');
+Yii::debug($data, __METHOD__);
```

### ReplaceWhereEqualityConditionWithArrayRector

Replace a single-column string `where()`/`andWhere()`/`orWhere()` condition (interpolated or concatenated) with the safer array condition format

```diff
-$query->where("column = $value");
-$query->andWhere('column = ' . $value);
+$query->where(['column' => $value]);
+$query->andWhere(['column' => $value]);
```

<!-- rules-list:end -->
