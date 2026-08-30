<?php

namespace App;

class SomeClass extends \yii\base\BaseObject
{
}

class SomeService
{
    public function run(): string
    {
        return SomeClass::className();
    }
}

-----
<?php

namespace App;

class SomeClass extends \yii\base\BaseObject
{
}

class SomeService
{
    public function run(): string
    {
        return \App\SomeClass::class;
    }
}
