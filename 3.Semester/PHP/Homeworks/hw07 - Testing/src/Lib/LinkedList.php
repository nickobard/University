<?php declare(strict_types=1);

namespace HW\Lib;

class LinkedList
{
    protected ?LinkedListItem $first = null;

    protected ?LinkedListItem $last = null;

    public function getFirst(): ?LinkedListItem
    {
        return $this->first;
    }

    public function setFirst(?LinkedListItem $first): LinkedList
    {
        $this->first = $first;
        return $this;
    }

    public function getLast(): ?LinkedListItem
    {
        return $this->last;
    }

    public function setLast(?LinkedListItem $last): LinkedList
    {
        $this->last = $last;
        return $this;
    }

    /**
     * Place new item at the begining of the list
     */
    public function prependList(string $value): LinkedListItem
    {
        $item = new LinkedListItem($value);
        if (is_null($this->first)) {
            $this->setFirst($item);
            $this->setLast($item);
            return $item;
        }
        $second = $this->getFirst();
        $this->setFirst($item);
        $item->setNext($second);
        $second->setPrev($item);

        return $item;
    }

    /**
     * Place new item at the end of the list
     */
    public function appendList(string $value): LinkedListItem
    {
        $item = new LinkedListItem($value);
        if (is_null($this->first)) {
            $this->setFirst($item);
            $this->setLast($item);
            return $item;
        }
        $penultimate = $this->getLast();
        $penultimate->setNext($item);
        $item->setPrev($penultimate);
        $this->setLast($item);

        return $item;
    }

    /**
     * Insert item before $nextItem and maintain continuity
     */
    public function prependItem(LinkedListItem $nextItem, string $value): LinkedListItem
    {
        $item = new LinkedListItem($value);
        $item->setNext($nextItem);
        $item->setPrev($nextItem->getPrev());
        $nextItem->getPrev()->setNext($item);
        $nextItem->setPrev($item);

        return $item;
    }

    /**
     * Insert item after $prevItem and maintain continuity
     */
    public function appendItem(LinkedListItem $prevItem, string $value): LinkedListItem
    {
        $item = new LinkedListItem($value);
        $item->setPrev($prevItem);
        $item->setNext($prevItem->getNext());
        $prevItem->getNext()->setPrev($item);
        $prevItem->setNext($item);
        return $item;
    }
}
