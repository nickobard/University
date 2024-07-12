<?php

namespace App\Model;

trait IdentifiableTrait
{
    protected ?int $id = null;

    public function getId(): ?int
    {
        return $this->id;
    }

}