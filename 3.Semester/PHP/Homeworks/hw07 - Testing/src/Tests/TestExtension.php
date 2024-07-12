<?php

namespace HW\Tests;

use PHPUnit\Runner\BeforeTestHook;

final class TestExtension implements BeforeTestHook
{

    public function executeBeforeTest(string $test): void
    {
        echo "Starting new test..." . PHP_EOL;
    }

}