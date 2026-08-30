<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

class ProductWithCodeExampleDescription extends BaseObject
{
    /** @return string See `$product->getFormattedSkuForInvoiceExportWithTaxAndCurrencyIncluded()` for details. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
-----
<?php

namespace MSpirkov\Yii2\Rector\Tests\Rules\AddPropertyTagsRector\Fixture\DescriptionLineLength;

use yii\base\BaseObject;

/**
 * @property-read string $sku See
 * `$product->getFormattedSkuForInvoiceExportWithTaxAndCurrencyIncluded()`
 * for details.
 */
class ProductWithCodeExampleDescription extends BaseObject
{
    /** @return string See `$product->getFormattedSkuForInvoiceExportWithTaxAndCurrencyIncluded()` for details. */
    public function getSku(): string
    {
        return 'SKU-1';
    }
}
