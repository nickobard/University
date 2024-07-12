<?php declare(strict_types=1);

namespace FinalTask\Triangle;

use Exception;

class Triangle
{
    // epsilon for float comparison
    const EPSILON = 0.0001;

    /**
     * @throws Exception
     */
    public function __construct(private readonly float|int $a, private readonly float|int $b, private readonly float|int $c)
    {
        if ($a + $b < $c ||
            $a + $c < $b ||
            $b + $c < $a)
            throw new Exception;
    }


    /**
     * @return float|int
     */
    public function getA(): float|int
    {
        return $this->a;
    }

    /**
     * @return float|int
     */
    public function getB(): float|int
    {
        return $this->b;
    }

    /**
     * @return float|int
     */
    public function getC(): float|int
    {
        return $this->c;
    }

    public function isRight(): bool
    {
        $sides = $this->getSides();
        $hypot = $sides[2];
        $a = $sides[0];
        $b = $sides[1];
        $lhs = pow($a, 2) + pow($b, 2);
        $rhs = pow($hypot, 2);
        return self::doubleEps($lhs, $rhs);
    }

    public function isEquilateral(): bool
    {
        return $this->a === $this->b && $this->b === $this->c;
    }

    public function isIsosceles(): bool
    {
        return $this->a === $this->b || $this->a === $this->c || $this->b === $this->c;
    }

    public function perimeter(): float|int
    {
        return $this->a + $this->b + $this->c;
    }

    public function getSides(): array
    {
        $sides = [$this->a, $this->b, $this->c];
        sort($sides);
        return $sides;
    }

    public static function doubleEps($a, $b): bool
    {
        return abs($a - $b) < self::EPSILON;
    }

    public static function isSimilar(Triangle $t1, Triangle $t2): bool
    {
        $t1_sides = $t1->getSides();
        $t2_sides = $t2->getSides();

        $aRatio = self::getRatio($t1_sides[0], $t2_sides[0]);
        $bRatio = self::getRatio($t1_sides[1], $t2_sides[1]);
        $cRatio = self::getRatio($t1_sides[2], $t2_sides[2]);

        if (!self::doubleEps($aRatio, $bRatio) || !self::doubleEps($bRatio, $cRatio))
            return false;
        return true;
    }

    public static function getRatio($a, $b): float|int
    {
        if ($a == 0 || $b == 0)
            return 0;
        return $a / $b;
    }
}
