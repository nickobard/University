<?php declare(strict_types=1);

namespace FinalTask\Events;

use PDO;

class Event
{
    protected static ?PDO $pdo = null;
    private ?int $id = null;
    private string $title;
    private string $date;
    private string $venue;

    public function generateId(): int
    {
        static $counter = 1;
        return $counter++;
    }

    public static function setDb(PDO $pdo): void
    {
        self::$pdo = $pdo;
    }

    public static function createDbTable(): void
    {
        $tableName = static::getTableName();

        self::$pdo->query("CREATE TABLE IF NOT EXISTS $tableName (
            id INTEGER not null constraint event_pk primary key,
            title TEXT not null,
            date TEXT not null,
            venue TEXT not null
        )")->execute();

    }

    public function save(): void
    {
        $tableName = static::getTableName();

        if (is_null($this->id)) {
            $this->id = $this->generateId();
            $query = "INSERT INTO $tableName (id, title, date, venue) VALUES (:id, :title, :date, :venue)";
            $data = ['id' => $this->id, 'title' => $this->title, 'date' => $this->date, 'venue' => $this->venue];
        } else if (is_null(self::findById($this->id))) {
            $query = "INSERT INTO $tableName (id, title, date, venue) VALUES (:id, :title, :date, :venue)";
            $data = ['id' => $this->id, 'title' => $this->title, 'date' => $this->date, 'venue' => $this->venue];
        } else {
            $query = "UPDATE $tableName SET title = :title, date = :date, venue = :venue
             WHERE id = :id";
            $data = ['title' => $this->title, 'date' => $this->date, 'venue' => $this->venue, 'id' => $this->id];
        }

        $statement = self::$pdo->prepare($query);
        $statement->execute($data);
    }

    public static function findById(?int $id): ?Event
    {
        $tableName = static::getTableName();
        $query = "SELECT * FROM $tableName WHERE id = :id";
        $queryData = ['id' => $id];
        $statement = self::$pdo->prepare($query);
        if (!$statement->execute($queryData))
            return null;
        $data = $statement->fetchAll();
        if (count($data) === 0)
            return null;
        return self::fromArray($data[0]);
    }

    /** @return Event[] */
    public static function findByVenueAndDate($venue, $date = null): array
    {
        $tableName = static::getTableName();
        if (is_null($date)) {
            $query = "SELECT DISTINCT *
            FROM $tableName
            WHERE venue = :venue";
            $data = ['venue' => $venue];
        } else {
            $query = "SELECT DISTINCT *
            FROM $tableName
            WHERE venue = :venue AND date = :date";
            $data = ['venue' => $venue, 'date' => $date];
        }
        $statement = self::$pdo->prepare($query);
        if (!$statement->execute($data))
            return [];

        $events = [];
        foreach ($statement->fetchAll() as $eventData) {
            $events[] = self::fromArray($eventData);
        }
        return $events;
    }

    public static function fromArray(array $data): ?Event
    {
        if (!isset($data['id']) || !isset($data['title']) || !isset($data['date']) || !isset($data['venue']))
            return null;
        $event = new Event();
        $event->setId($data['id']);
        $event->setTitle($data['title']);
        $event->setDate($data['date']);
        $event->setVenue($data['venue']);

        return $event;
    }

    public static final function getTableName(): string
    {
        return "events";
    }

    /**
     * @return int
     */
    public function getId(): int
    {
        return $this->id;
    }

    /**
     * @param int $id
     */
    public function setId(?int $id): void
    {
        $this->id = $id;
    }

    /**
     * @return string
     */
    public function getTitle(): string
    {
        return $this->title;
    }

    /**
     * @param string $title
     */
    public function setTitle(string $title): void
    {
        $this->title = $title;
    }

    /**
     * @return string
     */
    public function getDate(): string
    {
        return $this->date;
    }

    /**
     * @param string $date
     */
    public function setDate(string $date): void
    {
        $this->date = $date;
    }

    /**
     * @return string
     */
    public function getVenue(): string
    {
        return $this->venue;
    }

    /**
     * @param string $venue
     */
    public function setVenue(string $venue): void
    {
        $this->venue = $venue;
    }


}
