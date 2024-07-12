<?php declare(strict_types=1);

namespace App;

use PDO;

class Db
{
    private const DSN = 'pgsql:host=postgres;port=5432;dbname=devdb;';
    private const USER = 'dev';
    private const PASSWORD = 'pass';

    protected static ?PDO $pdo = null;

    public static function get(): PDO
    {
        return self::$pdo ?? (self::$pdo = new PDO(
            self::DSN,
            self::USER,
            self::PASSWORD,
            [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
            ]
        ));
    }
}
