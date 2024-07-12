<?php declare(strict_types=1);

namespace App\Model;

use App\Db;

class Account extends AbstractModel
{

    public function __construct(
        protected string $number,
        protected string $code,
        int              $id = null
    )
    {
        $this->id = $id;
    }

    /**
     * Creates DB table using CREATE TABLE ...
     */
    public static function createTable(): void
    {
        $tableName = static::getTableName();

        Db::get()->query("CREATE TABLE IF NOT EXISTS $tableName (
            id serial not null constraint account_pk primary key,
            number text not null,
            code text not null
        )");
    }

    /**
     * Drops DB table using DROP TABLE ...
     */
    public static function dropTable(): void
    {
        $tableName = static::getTableName();
        Db::get()->query("DROP TABLE IF EXISTS $tableName");
    }

    /**
     * Find account record by number and bank code
     */
    public static function find(string $number, string $code): ?Account
    {
        $tableName = static::getTableName();
        $query = "SELECT * FROM $tableName WHERE number = :number AND code = :code";
        $queryData = ['number' => $number, 'code' => $code];
        $statement = Db::get()->prepare($query);
        if (!$statement->execute($queryData))
            return null;
        $data = $statement->fetchAll();
        return empty($data) ? null : self::fromArray($data[0]);
    }

    /**
     * Find account record by id
     */
    public static function findById(int $id): ?self
    {
        $tableName = static::getTableName();
        $query = "SELECT * FROM $tableName WHERE id = :id";
        $queryData = ['id' => $id];
        $statement = Db::get()->prepare($query);
        if (!$statement->execute($queryData))
            return null;
        $data = $statement->fetchAll();
        return self::fromArray($data[0]);
    }

    /**
     * Inserts new account record and returns its instance; or returns existing account instance
     */
    public static function findOrCreate(string $number, string $code): self
    {
        if (is_null($existingAccount = self::find(number: $number, code: $code))) {
            $newAccount = new Account(number: $number, code: $code);
            $newAccount->save();
            return $newAccount;
        } else
            return $existingAccount;

    }

    /**
     * Returns iterable of Transaction instances related to this Account, consider both transaction direction
     *
     * @return iterable<Transaction>
     */
    public function getTransactions(): iterable
    {
        $accountTableName = Account::getTableName();
        $transactionTableName = Transaction::getTableName();
        $query = "SELECT DISTINCT t.* 
                    FROM $transactionTableName t JOIN $accountTableName a 
                    ON t.account_from = a.id  OR t.account_to = a.id 
                    WHERE  a.id = :id";
        $statement = Db::get()->prepare($query);
        $data = ['id' => $this->id];

        if (!$statement->execute($data))
            return [];

        $transactions = [];
        foreach ($statement->fetchAll() as $accountData) {
            $transactions[] = Transaction::fromArray($accountData);
        }
        return $transactions;
    }

    /**
     * Returns transaction sum (using SQL aggregate function). Treat outgoing transactions as 'minus' and incoming as 'plus'.
     */
    public function getTransactionSum(): float
    {
        return array_reduce($this->getTransactions(), fn(float $sum, Transaction $t): float =>
            $this->id === $t->getTo()->getId() ? $sum + $t->getAmount() : $sum - $t->getAmount(), 0);
    }

    public function save(): bool
    {
        $tableName = static::getTableName();

        if (is_null($this->id)) {
            $query = "INSERT INTO $tableName (number, code) VALUES (:number, :code)";
            $data = ['number' => $this->number, 'code' => $this->code];
        } else {
            $query = "UPDATE $tableName SET (number, code) = (:number, :code) 
            WHERE id = :id";
            $data = ['number' => $this->number, 'code' => $this->code, 'id' => $this->id];
        }

        $statement = Db::get()->prepare($query);

        if (!$statement->execute($data))
            return false;

        if (is_null($this->id))
            $this->id = intval(Db::get()->lastInsertId());
        return true;
    }

    public static function fromArray(array $data): ?Account
    {
        if (!isset($data['number']) || !isset($data['code']) || !isset($data['id']))
            return null;
        return new Account(number: $data['number'], code: $data['code'], id: $data['id']);
    }

    public function getNumber(): string
    {
        return $this->number;
    }

    public function setNumber(string $number): Account
    {
        $this->number = $number;
        return $this;
    }

    public function getCode(): string
    {
        return $this->code;
    }

    public function setCode(string $code): Account
    {
        $this->code = $code;
        return $this;
    }

    public function __toString(): string
    {
        return "{$this->number}/{$this->code}";
    }

    public static final function getTableName(): string
    {
        return "account";
    }

}
