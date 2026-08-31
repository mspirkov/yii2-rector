<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\SpeedBase;

class VehicleWithLocalSetterAndInheritedGetter extends SpeedBase
{
    public function setSpeed(int $speed): void
    {
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\Main;

use MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Source\SpeedBase;

/**
 * @property int $speed The current speed, in km/h.
 */
class VehicleWithLocalSetterAndInheritedGetter extends SpeedBase
{
    public function setSpeed(int $speed): void
    {
    }
}
