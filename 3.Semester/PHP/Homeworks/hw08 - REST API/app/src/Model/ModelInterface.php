<?php declare(strict_types=1);

namespace Books\Model;

interface ModelInterface
{
    /**
     * Returns database table name
     * @return string table name
     */
    public static function getTableName(): string;

    /**
     * Return sequence name
     * @return string sequence name
     */
    public static function getSequenceName(): string;

    /**
     * Create object from given data array
     * @param array $data data
     * @return AbstractModel|null
     */
    public static function fromArray(array $data): ?AbstractModel;

    /**
     * Convert current object to data array
     * @return array data
     */
    public function toArray(): array;
}
