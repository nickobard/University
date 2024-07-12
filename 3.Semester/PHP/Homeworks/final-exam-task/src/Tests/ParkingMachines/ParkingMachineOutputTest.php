<?php declare(strict_types=1);

namespace FinalTask\Tests\ParkingMachines;

use Generator;

class ParkingMachineOutputTest extends AbstractParkingMachineTest
{
    public function dataProvider(): Generator
    {
        yield [
            '14.445391089000054',
            '50.09868634400004',
            'Nejbližší parkovací automat je asi 0.36 km daleko, nachází se v městské části P7, v celé městské části P7 je celkem 94 parkovacích automatů, https://maps.google.com/maps?q=50.101709873,14.444108889' . PHP_EOL,
        ];
        yield [
            '14.49',
            '50.15',
            'Nejbližší parkovací automat je asi 1.90 km daleko, nachází se v městské části P8, v celé městské části P8 je celkem 101 parkovacích automatů, https://maps.google.com/maps?q=50.136812557,14.478579329' . PHP_EOL
        ];
        yield [
            '14.3897809',
            '50.1050877',
            'Nejbližší parkovací automat je asi 0.11 km daleko, nachází se v městské části P6, v celé městské části P6 je celkem 211 parkovacích automatů, https://maps.google.com/maps?q=50.105065379,14.390737984' . PHP_EOL
        ];
        yield [
            '14.3646',
            '49.9858',
            'Nejbližší parkovací automat je asi 1.30 km daleko, nachází se v městské části P16, v celé městské části P16 je celkem 1 parkovacích automatů, https://maps.google.com/maps?q=49.980587967,14.354032444' . PHP_EOL
        ];
        yield [
            '15.5065294',
            '50.6088964',
            'Nejbližší parkovací automat je asi 118.40 km daleko, nachází se v městské části P22, v celé městské části P22 je celkem 3 parkovacích automatů, https://maps.google.com/maps?q=50.031450005,14.599440011' . PHP_EOL
        ];
    }

    /** @dataProvider dataProvider */
    public function testCommandOutput($latitude, $longitude, $output): void
    {
        $this->commandTester->execute(['parking:machine', '--latitude' => $latitude, '--longitude' => $longitude]);
        $this->commandTester->assertCommandIsSuccessful();
        $this->assertEquals($output, $this->commandTester->getDisplay());
    }
}
