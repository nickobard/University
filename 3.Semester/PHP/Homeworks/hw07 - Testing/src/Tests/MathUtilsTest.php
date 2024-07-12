<?php declare(strict_types=1);

namespace HW\Tests;

use PHPUnit\Framework\TestCase;
use HW\Lib\MathUtils;

/** @covers \HW\Lib\MathUtils */
final class MathUtilsTest extends TestCase
{

    public function testSum(): void
    {
        $this->assertSame(3, MathUtils::sum([1, 2]));
        $this->assertSame(1, MathUtils::sum([1]));
        $this->assertSame(30, MathUtils::sum([10, 10, 10]));
        $this->assertSame(10, MathUtils::sum([10, -10, 10]));
        $this->assertSame(0, MathUtils::sum([]));
        $this->assertSame(0, MathUtils::sum([0, 0, 0, 0]));
        $this->assertEquals("0", MathUtils::sum([0, 0]));

        $this->assertNotSame("0", MathUtils::sum([0, 0]));
        $this->assertNotEquals("22", MathUtils::sum([1, 1]));
    }

    /** @dataProvider _solveLinearProvider */
    public function testSolveLinear(int|float $result, $a, $b): void
    {
        $this->assertEquals($result, MathUtils::solveLinear($a, $b));
    }

    public function _solveLinearProvider(): \Generator
    {
        yield [3, -2, 6];
        yield [1, 1, -1];
        yield [-1, 1, 1];
        yield [1, -1, 1];
        yield [0.5, 2, -1];
    }

    public function testSolveLinearNegative(): void
    {
        $this->assertNotEquals(-10, MathUtils::solveLinear(1, 1));
    }

    public function testSolveLinearExceptionThrow(): void
    {
        $this->expectException(\InvalidArgumentException::class);
        MathUtils::solveLinear(0, 10);
    }

    /** @dataProvider _solveQuadraticProvider */
    public function testSolveQuadratic(array $result, array $input): void
    {
        $this->assertEquals($result, MathUtils::solveQuadratic(...$input));
    }

    public function _solveQuadraticProvider(): \Generator
    {
        yield [[-1, -1], [1, 2, 1]];
        yield [[1, 1], [1, -2, 1]];
        yield [[-1, -2], [1, 3, 2]];
    }

    public function testSolveQuadraticShouldThrowException(): void
    {
        $this->expectException(\InvalidArgumentException::class);
        MathUtils::solveQuadratic(1, 1, 1);
    }

    public function testSolveQuadraticNegative(): void
    {
        $this->assertNotEquals([42, 69], [1, 2, 1]);
    }

}
