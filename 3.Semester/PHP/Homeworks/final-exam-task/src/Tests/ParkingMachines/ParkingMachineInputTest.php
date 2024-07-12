<?php declare(strict_types=1);

namespace FinalTask\Tests\ParkingMachines;

use Exception;

class ParkingMachineInputTest extends AbstractParkingMachineTest
{
    public function testCommandInput(): void
    {
        try {
            $this->commandTester->execute(['parking:machine', '--latitude' => 14, '--longitude' => 50]);
        } catch (Exception) {
            $this->fail('Failed asserting that command accepts --latitude and --longitude options');
        }
        $this->assertArrayHasKey(
            'latitude',
            $this->commandTester->getInput()->getOptions(),
            "Failed asserting that command accepts --latitude option"
        );
        $this->assertArrayHasKey(
            'longitude',
            $this->commandTester->getInput()->getOptions(),
            "Failed asserting that command accepts --longitude option"
        );
    }
}
