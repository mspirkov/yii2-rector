<?php

declare(strict_types=1);

namespace MSpirkov\Yii2\Rector\Rules;

use PhpParser\Node;
use PhpParser\Node\Expr;
use PhpParser\Node\Expr\PropertyFetch;
use PhpParser\Node\Expr\StaticPropertyFetch;
use PhpParser\Node\Expr\Variable;
use PHPStan\Type\ObjectType;
use Rector\Rector\AbstractRector;
use Symplify\RuleDocGenerator\Contract\DocumentedRuleInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;
use yii\BaseYii;
use yii\base\Controller;

final class ReplaceAppRequestResponseWithThisRector extends AbstractRector implements DocumentedRuleInterface
{
    /** @var list<string> */
    private const PROPERTY_NAMES = ['request', 'response'];

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition(
            'Replace `Yii::$app->request`/`Yii::$app->response` with `$this->request`/`$this->response` '
            . 'inside a `yii\base\Controller` subclass — the controller already exposes the same request/'
            . 'response objects through its own properties',
            [
                new CodeSample(
                    <<<'CODE_SAMPLE'
                        class SiteController extends Controller
                        {
                            public function actionIndex()
                            {
                                Yii::$app->response->format = Response::FORMAT_JSON;

                                $ip = Yii::$app->request->getUserIP();
                            }
                        }
                        CODE_SAMPLE
                    ,
                    <<<'CODE_SAMPLE'
                        class SiteController extends Controller
                        {
                            public function actionIndex()
                            {
                                $this->response->format = Response::FORMAT_JSON;

                                $ip = $this->request->getUserIP();
                            }
                        }
                        CODE_SAMPLE
                ),
            ]
        );
    }

    public function getNodeTypes(): array
    {
        return [PropertyFetch::class];
    }

    /**
     * @param PropertyFetch $node
     */
    public function refactor(Node $node): ?Node
    {
        $propertyName = $this->getName($node->name);
        if ($propertyName === null || !in_array($propertyName, self::PROPERTY_NAMES, true)) {
            return null;
        }

        if (!$this->isAppPropertyFetch($node->var)) {
            return null;
        }

        if (!$this->isCurrentThisControllerType($node)) {
            return null;
        }

        return new PropertyFetch(new Variable('this'), $propertyName);
    }

    private function isAppPropertyFetch(Expr $expr): bool
    {
        if (!$expr instanceof StaticPropertyFetch) {
            return false;
        }

        if (!$this->isName($expr->name, 'app')) {
            return false;
        }

        return $this->isObjectType($expr->class, new ObjectType(BaseYii::class));
    }

    private function isCurrentThisControllerType(Node $node): bool
    {
        $thisVariable = new Variable('this');
        $thisVariable->setAttributes($node->getAttributes());

        return $this->isObjectType($thisVariable, new ObjectType(Controller::class));
    }
}
