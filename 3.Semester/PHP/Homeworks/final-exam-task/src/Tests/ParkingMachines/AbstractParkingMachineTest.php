<?php declare(strict_types=1);

namespace FinalTask\Tests\ParkingMachines;

use FinalTask\ParkingMachines\ParkingMachineCommand;
use PHPUnit\Framework\TestCase;
use Symfony\Component\Console\Application;
use Symfony\Component\Console\Tester\CommandTester;

abstract class AbstractParkingMachineTest extends TestCase
{
    protected CommandTester $commandTester;

    public function setUp(): void
    {
        $app = new Application();
        $app->add(new ParkingMachineCommand());
        $this->commandTester = new CommandTester($app->find('parking:machine'));
    }

    protected function tearDown(): void
    {
        unset($this->commandTester);
    }
}
