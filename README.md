<p align="center">
    <a href="https://github.com/yiisoft" target="_blank">
        <img src="https://avatars0.githubusercontent.com/u/993323" height="100px">
    </a>
    <h1 align="center">Yii2 Rector</h1>
</p>

A set of [Rector](https://getrector.com) rules for Yii2 projects that I put together for my own day-to-day work.
They make refactoring a Yii2 codebase easier and help keep it cleaner, automating the framework-specific patterns
— magic properties, `ActiveRecord`/`Query` calls, accumulated deprecations — that a generic Rector set has no way
to know about.

[![PHP](https://img.shields.io/badge/%3E%3D7.4-7A86B8.svg?style=for-the-badge&logo=php&logoColor=white&label=PHP)](https://www.php.net/releases/7_4_0.php)
[![Yii2](https://img.shields.io/badge/%3E%3D2.0.53-247BA0.svg?style=for-the-badge&logo=yii&logoColor=white&label=Yii)](https://github.com/yiisoft/yii2/releases/tag/2.0.53)
[![Rector](https://img.shields.io/badge/%3E%3D2.6.0-247BA0.svg?style=for-the-badge&label=Rector)](https://github.com/rectorphp/rector/releases/tag/2.6.0)
[![Tests](https://img.shields.io/github/actions/workflow/status/mspirkov/yii2-rector/ci.yml?branch=main&style=for-the-badge&logo=github&label=Tests)](https://github.com/mspirkov/yii2-rector/actions/workflows/ci.yml)
[![Coverage](https://img.shields.io/codecov/c/github/mspirkov/yii2-rector.svg?branch=main&style=for-the-badge&logo=codecov&logoColor=white&label=Coverage)](https://codecov.io/github/mspirkov/yii2-rector)
![PHPStan Level Max](https://img.shields.io/badge/Max-7A86B8.svg?style=for-the-badge&label=PHPStan%20Level)

## Support

If you like this project, give it a ⭐ on [GitHub](https://github.com/mspirkov/yii2-rector) — it helps others
discover it.

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
    ->withPaths([__DIR__ . '/src'])
    ->withSets([
        Yii2SetList::MAIN,
    ]);
```

## Rules at a glance

<!-- rules-table:start -->

| Rule | Description |
| --- | --- |
| [AddPropertyTagsRector](#addpropertytagsrector) | Add (or correct) `@property`/`@property-read`/`@property-write` tags on a `yii\base\BaseObject` subclass, based on its own `getXxx()`/`setXxx()` method pairs and ActiveRecord relation getters (`hasOne()`/`hasMany()`). |
| [MergeModelRulesRector](#mergemodelrulesrector) | Merge `yii\base\Model::rules()` entries that configure the same validator with the same options but a different attribute into one entry, combining their attributes into a single array (an attribute already present in another merged entry is not duplicated). |
| [RemoveRedundantHtmlEncodeRector](#removeredundanthtmlencoderector) | Remove a `yii\helpers\Html::encode()` call whose `$content` argument PHPStan proves is a numeric string — digits only can't contain a character `htmlspecialchars()` would touch, so the call is replaced by its bare `$content` argument (a trailing `$doubleEncode` argument, if present, is dropped too: it can't affect a string with nothing to double-encode). |
| [ReplaceClassnameWithClassRector](#replaceclassnamewithclassrector) | Replace the deprecated `yii\base\BaseObject::className()` call with the native `::class` constant. |
| [ReplaceExistenceCheckWithExistsRector](#replaceexistencecheckwithexistsrector) | Replace an existence check on a `yii\db\QueryInterface` result (`yii\db\Query`, `yii\db\ActiveQuery`, ...) with the cheaper `->exists()` call. |
| [ReplaceFindWhereAllWithFindAllRector](#replacefindwhereallwithfindallrector) | Replace `find()->where([...])->all()` on an ActiveRecord class with the equivalent `findAll([...])`. |
| [ReplaceFindWhereOneWithFindOneRector](#replacefindwhereonewithfindonerector) | Replace `find()->where([...])->one()` on an ActiveRecord class with the equivalent `findOne([...])`. |
| [ReplaceGetterWithPropertyRector](#replacegetterwithpropertyrector) | Replace a `yii\base\BaseObject` getter call with the equivalent magic-property access, when the property is documented via a class-level `@property` or `@property-read` tag whose type matches the getter's return type, and there is no public native property of the same name (which would bypass the getter entirely) |
| [ReplaceSetterWithPropertyRector](#replacesetterwithpropertyrector) | Replace a `yii\base\BaseObject` setter call with the equivalent magic-property assignment, when the property is documented via a class-level `@property` or `@property-write` tag whose type matches the setter's parameter type, and there is no public native property of the same name (which would bypass the setter entirely) |
| [ReplaceWhereEqualityConditionWithArrayRector](#replacewhereequalityconditionwitharrayrector) | Replace a single-column string `where()`/`andWhere()`/`orWhere()` condition (interpolated or concatenated) with the safer array condition format |

<!-- rules-table:end -->

## Rule reference

<!-- rules-list:start -->

### AddPropertyTagsRector

Add (or correct) `@property`/`@property-read`/`@property-write` tags on a `yii\base\BaseObject` subclass, based on its own `getXxx()`/`setXxx()` method pairs and ActiveRecord relation getters (`hasOne()`/`hasMany()`). Configurable via `skippedClasses` — a plain array value (e.g. `'App\Foo'`) fully skips a class, while a string key mapped to a list of property names (e.g. `'App\Bar' => ['name']`) skips only those properties — and `descriptionLineLength` (wrap width for copied tag descriptions, 110 by default)

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

Merge `yii\base\Model::rules()` entries that configure the same validator with the same options but a different attribute into one entry, combining their attributes into a single array (an attribute already present in another merged entry is not duplicated). This is behavior-preserving: Yii2 builds one validator instance per rule entry and applies it to every attribute of that entry independently, so `[['login', 'password'], 'required']` runs exactly like the two separate `['login', 'required']` / `['password', 'required']` entries it replaces. Two entries only merge when everything after the attribute(s) — the validator and any options — is identical; a `rules()` body that isn't a single `return [...]` of literal rule arrays, or an entry whose shape doesn't look like `[attribute(s), validator, ...options]`, is left untouched

```diff
 class LoginForm extends \yii\base\Model
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

Remove a `yii\helpers\Html::encode()` call whose `$content` argument PHPStan proves is a numeric string — digits only can't contain a character `htmlspecialchars()` would touch, so the call is replaced by its bare `$content` argument (a trailing `$doubleEncode` argument, if present, is dropped too: it can't affect a string with nothing to double-encode). Any other `$content` (a non-numeric string, a variable of unknown or non-string type, `int`/`float`/`bool`, `null`, an array, an object, ...) is left untouched

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

### ReplaceClassnameWithClassRector

Replace the deprecated `yii\base\BaseObject::className()` call with the native `::class` constant. `self::className()` and `parent::className()` are left untouched: both are late-static-binding *forwarding* calls, so they are not generally equivalent to the compile-time `self::class`/`parent::class` once the surrounding class is subclassed — only `static::className()` and an explicit `SomeClass::className()` are safe to rewrite unconditionally

```diff
-$class = SomeClass::className();
-$class = static::className();
+$class = SomeClass::class;
+$class = static::class;
```

### ReplaceExistenceCheckWithExistsRector

Replace an existence check on a `yii\db\QueryInterface` result (`yii\db\Query`, `yii\db\ActiveQuery`, ...) with the cheaper `->exists()` call. Two shapes are recognised: a `->count()` comparison against the boundary literals `0`/`1` (`>`, `>=`, `<`, `<=`, `===`, `!==`, `==`, `!=`/`<>`, in either operand order), and a strict `->one() !== null` / `->one() === null` check. `count()` issues a `SELECT COUNT(*)` and `one()` fetches (and hydrates) a full row just to test for presence, while `exists()` issues a cheaper `SELECT 1 ... LIMIT 1` — worthwhile whenever the code only cares whether any row matches, not the exact count or the row itself. Checks that mean "no rows" (e.g. `count() < 1`, `count() === 0`, `one() === null`) are rewritten to the negated `!exists()`, not `exists()` — the two calls are not interchangeable, so it is worth a second look when reading the diff. Only the two literal boundaries that map unambiguously onto a presence/absence question are recognised: `count() > 1`, for instance, asks a different question and is left untouched.

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

### ReplaceGetterWithPropertyRector

Replace a `yii\base\BaseObject` getter call with the equivalent magic-property access, when the property is documented via a class-level `@property` or `@property-read` tag whose type matches the getter's return type, and there is no public native property of the same name (which would bypass the getter entirely)

```diff
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

### ReplaceWhereEqualityConditionWithArrayRector

Replace a single-column string `where()`/`andWhere()`/`orWhere()` condition (interpolated or concatenated) with the safer array condition format

```diff
-$query->where("column = $value");
-$query->andWhere('column = ' . $value);
+$query->where(['column' => $value]);
+$query->andWhere(['column' => $value]);
```

<!-- rules-list:end -->
