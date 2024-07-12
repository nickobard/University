<?php declare(strict_types=1);

namespace Books\Database;

use PDO;

class Database
{
    private const DSN = "pgsql:host=postgres;port=5432;dbname=devdb;";
    private const USER = "dev";
    private const PASSWORD = "pass";

    private static ?PDO $db = null;

    public static function getConnection(): PDO
    {
        if (self::$db === null) {
            self::$db = new PDO(self::DSN, self::USER, self::PASSWORD);
        }
        return self::$db;
    }
}
