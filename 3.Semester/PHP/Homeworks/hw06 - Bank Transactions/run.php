<?php declare(strict_types=1);

use App\Model\Account;
use App\Model\Transaction;

ini_set('error_reporting', E_ALL);
ini_set('display_errors', 'On');

require_once __DIR__ . '/vendor/autoload.php';

function init(): void
{
    Transaction::dropTable();
    Transaction::createTable();
    Account::dropTable();
    Account::createTable();
}

function import(string $filename): void
{
    $data = explode(PHP_EOL, file_get_contents($filename));
    foreach ($data as $row) {
        $col = explode(' ', $row);
        if (count($col) !== 5) {
            continue;
        }
        $from = Account::findOrCreate($col[0], $col[1]);
        $to = Account::findOrCreate($col[2], $col[3]);
        $transaction = new Transaction($from, $to, (float)$col[4]);
        $transaction->insert();
    }
}

function summary(string $number, string $code): void
{
    $account = Account::find($number, $code);
    /** @var Transaction $transaction */
    foreach ($account->getTransactions() as $transaction) {
        printf("%s\t->\t%s\tCZK %.2f" . PHP_EOL, $transaction->getFrom(), $transaction->getTo(), $transaction->getAmount());
    }
    printf("SUMMARY:\t\t\t\tCZK %.2f" . PHP_EOL . PHP_EOL, $account->getTransactionSum());
}

// init
if ($argc === 2 && $argv[1] === 'init') {
    init();

    return;
}

// import
if ($argc === 3 && $argv[1] === 'import') {
    import($argv[2]);

    return;
}

// summary
if ($argc === 4 && $argv[1] === 'summary') {
    summary($argv[2], $argv[3]);

    return;
}

echo <<<USAGE
    $argv[0] <command> <arguments...>
    commands:
      - init
      - import <filename>
      - summary <number> <code>

USAGE;
