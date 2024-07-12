<?php

namespace App\Model;

interface ModelInterface
{

    /**
     * Returns database table name
     * @return string table name
     */
    public static function getTableName(): string;

}