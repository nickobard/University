<?php declare(strict_types=1);

namespace FinalTask\Tests\Triangle;

use FinalTask\Triangle\Triangle;

trait TriangleTrait
{
    protected function getC(int|float $a, int|float $b): int
    {
        return random_int((int)(abs($a - $b) + Triangle::EPSILON), (int)($a + $b - Triangle::EPSILON));
    }
}
