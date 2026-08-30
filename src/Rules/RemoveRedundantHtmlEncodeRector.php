<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr\StaticCall;
use PHPStan\Type\ObjectType;
use Rector\PHPStan\ScopeFetcher;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\helpers\Html;

final class RemoveRedundantHtmlEncodeRector extends AbstractRector implements DocumentedRuleInterface
{
    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Remove a `yii\helpers\Html::encode()` call whose `$content` argument PHPStan proves '
            . 'is a numeric string — digits only can\'t contain a character `htmlspecialchars()` '
            . 'would touch, so the call is replaced by its bare `$content` argument (dropping a '
            . 'trailing `$doubleEncode` argument, if present, too). Any other `$content` is left '
            . 'untouched',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        <?php
                        /**
                         * @var numeric-string $id
                         * @var string $name
                         */
                        ?>
                        <?= Html::encode($id) ?>
                        <?= Html::encode($name) ?>
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        <?php
                        /**
                         * @var numeric-string $id
                         * @var string $name
                         */
                        ?>
                        <?= $id ?>
                        <?= Html::encode($name) ?>
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [StaticCall::class];
    }

    /**
     * @param StaticCall $node
     */
    public function refactor(Node $node): ?Node
    {
        $args = $node->getArgs();

        if (!isset($args[0]) || $args[0]->unpack) {
            return null;
        }

        $arg = $args[0];

        if (!$this->isName($node->name, 'encode')) {
            return null;
        }

        if (!$this->isObjectType($node->class, new ObjectType(Html::class))) {
            return null;
        }

        $scope = ScopeFetcher::fetch($node);

        if (!$scope->getType($arg->value)->isNumericString()->yes()) {
            return null;
        }

        return $arg->value;
    }
}
