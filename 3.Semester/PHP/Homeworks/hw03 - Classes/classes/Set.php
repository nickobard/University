<?php

/**
 * Represents bag, that can contain each item only once.
 */
class Set extends Bag
{

    public function add(mixed $item): void
    {
        if (!$this->contains($item))
            $this->items[$item] = true;
    }

    public function elementSize(mixed $item): int
    {
        if ($this->contains($item))
            return 1;
        return 0;
    }

    public function remove(mixed $item): void
    {
        if ($this->contains($item))
            unset($this->items[$item]);
    }

    public function size(): int
    {
        return count($this->items);
    }

}