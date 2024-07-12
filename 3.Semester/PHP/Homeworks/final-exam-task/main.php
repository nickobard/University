<?php declare(strict_types=1);

require __DIR__ . '/vendor/autoload.php';

use FinalTask\ParkingMachines\ParkingMachineCommand;
use Symfony\Component\Console\Application;

$app = new Application();

$app->add(new ParkingMachineCommand());

$app->run();

// Use this file to test whatever you need
