<?php declare (strict_types=1);

/**
 * Class that represent a bag of items, storing different items and their count number.
 */
class Bag
{

    /** @var array $items represents stored items. */
    protected array $items;

    /**
     * Constructor.
     */
    public function __construct()
    {
        $this->items = array();
    }

    /**
     * Adds item into the bag.
     * @param mixed $item to be added to the bag.
     * @return void
     */
    public function add(mixed $item): void
    {
        if ($this->contains($item))
            $this->items[$item] += 1;
        else
            $this->items[$item] = 1;
    }

    /**
     * Clear the bag out of items.
     * @return void
     */
    public function clear(): void
    {
        unset($this->items);
        $this->items = array();
    }

    /**
     * Check if item is in the bag or not.
     * @param mixed $item represents item to be checked if is in the bag.
     * @return bool true if item is in the bag.
     */
    public function contains(mixed $item): bool
    {
        return array_key_exists($item, $this->items);
    }

    /**
     * How many times the item is in the bag.
     * @param mixed $item item in the bag.
     * @return int count number of the item.
     */
    public function elementSize(mixed $item): int
    {
        if ($this->contains($item))
            return $this->items[$item];
        return 0;
    }

    /**
     * @return bool true if bag is empty.
     */
    public function isEmpty(): bool
    {
        return empty($this->items);
    }

    /**
     * @param mixed $item to be removed from the bag.
     * @return void
     */
    public function remove(mixed $item): void
    {
        if ($this->contains($item)) {
            if ($this->items[$item] > 1)
                $this->items[$item] -= 1;
            else
                unset($this->items[$item]);
        }

    }

    /**
     * @return int total number of items in the bag, counting for each item.
     */
    public function size(): int
    {
        return array_reduce($this->items, fn(int $sum, int $count): int => $sum + $count, 0);
    }
}
