<?php declare(strict_types=1);

namespace FinalTask\ParkingMachines;

use Symfony\Component\Console\Attribute\AsCommand;
use Symfony\Component\Console\Command\Command;
use Symfony\Component\Console\Input\InputInterface;
use Symfony\Component\Console\Output\OutputInterface;

#[AsCommand(name: 'parking:machine')]
class ParkingMachineCommand extends Command
{
    private const URL = 'https://opendata.iprpraha.cz/CUR/DOP/DOP_ZPS_Parkomaty_b/WGS_84/DOP_ZPS_Parkomaty_b.json';
    private const MAP_LINK = 'https://maps.google.com/maps?q=';

    protected function configure(): void
    {
        // TODO: configure options. Name them '--latitude' and '--longitude'. Short versions will not be used
    }

    protected function execute(InputInterface $input, OutputInterface $output): int
    {
        // TODO: read input options

        // TODO: download JSON from self::URL

        // TODO: calculate distances using 'haversine greater circle distance' (you can obtain this function from the internet)

        // TODO: write out the closest parking machine with additional details and map link (use self::MAP_LINK)

        return Command::SUCCESS;
    }
}
