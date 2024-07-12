<?php declare(strict_types=1);

namespace HW\Lib;

use function PHPUnit\Framework\throwException;

class MathUtils
{
    /**
     * Sum a list of numbers.
     */
    public static function sum(array $list): int
    {
        $sum = 0;
        $i = 0;

        while ($i < count($list)) {
            $sum += $list[$i++];
        }

        return $sum;
    }

    /**
     * Solve linear equation ax + b = 0.
     */
    public static function solveLinear($a, $b): float|int
    {
        if ($a === 0) {
            throw new \InvalidArgumentException();
        }

        return -$b / $a;
    }

    /**
     * Solve quadratic equation ax^2 + bx + c = 0.
     *
     * @return array Solution x1 and x2.
     */
    public static function solveQuadratic($a, $b, $c): array
    {
        $d = pow($b, 2) - 4 * $a * $c;
        if ($d < 0) {
            throw new \InvalidArgumentException();
        }

        $d = sqrt($d);

        $x1 = (-$b + $d) / (2 * $a);
        $x2 = (-$b - $d) / (2 * $a);
        return [$x1, $x2];
    }
}
