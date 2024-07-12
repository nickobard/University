<?php declare(strict_types=1);

namespace FinalTask\Tests\Triangle;

use FinalTask\Triangle\Triangle;
use PHPUnit\Framework\TestCase;

class TriangleSpecialTest extends TestCase
{
    use TriangleTrait;

    public function testRandomEquilateral(): void
    {
        $a = random_int(1, 100);

        $t = new Triangle($a, $a, $a);

        $this->assertTrue($t->isEquilateral(), "[$a, $a, $a] should be equilateral");
    }

    public function testRandomIsosceles(): void
    {
        $a = random_int(1, 100);
        $b = $this->getC($a, $a);

        $t = new Triangle($b, $a, $a);
        $this->assertTrue($t->isIsosceles(), "[$b, $a, $a] should be isosceles");

        $t = new Triangle($a, $b, $a);
        $this->assertTrue($t->isIsosceles(), "[$a, $b, $a] should be isosceles");

        $t = new Triangle($a, $a, $b);
        $this->assertTrue($t->isIsosceles(), "[$a, $a, $b] should be isosceles");
    }

    public function testRandomRight(): void
    {
        $a = random_int(1, 100);
        $b = random_int(1, 100);
        $c = sqrt($a * $a + $b * $b);

        $t = new Triangle($a, $b, $c);
        $this->assertTrue($t->isRight(), "[$a, $b, $c] should be right");

        $t = new Triangle($a, $c, $b);
        $this->assertTrue($t->isRight(), "[$a, $c, $b] should be right");

        $t = new Triangle($c, $a, $b);
        $this->assertTrue($t->isRight(), "[$c, $a, $b] should be right");
    }


    /** @dataProvider equilateralData */
    public function testEquilateral(int|float $a, int|float $b, int|float $c): void
    {
        $t = new Triangle($a, $b, $c);
        $this->assertTrue($t->isEquilateral());
    }

    public function equilateralData(): array
    {
        return [
            [0, 0, 0],
            [1, 1, 1],
            [42, 42, 42]
        ];
    }

    /** @dataProvider isoscelesData */
    public function testIsosceles(int|float $a, int|float $b, int|float $c): void
    {
        $t = new Triangle($a, $b, $c);
        $this->assertTrue($t->isIsosceles());
    }

    public function isoscelesData(): array
    {
        return [
            [16, 16, 18],
            [26, 18, 18],
            [37, 45, 37]
        ];
    }

    /** @dataProvider equilateralData */
    public function testEquilateralIsosceles(int|float $a, int|float $b, int|float $c): void
    {
        $t = new Triangle($a, $b, $c);
        $this->assertTrue($t->isIsosceles());
    }

    /** @dataProvider rightData */
    public function testRight(int|float $a, int|float $b, int|float $c): void
    {
        $t = new Triangle($a, $b, $c);

        $this->assertTrue($t->isRight());
    }

    public function rightData(): array
    {
        return [
            [3, 4, 5],
            [8, 6, 10],
            [15, 9, 12],
            [0, 0, 0]
        ];
    }
}
