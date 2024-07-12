<?php declare(strict_types=1);

namespace Iterator;

use Iterator;
use Node;
use OutOfBoundsException;

/**
 * Abstract class which represents iterator over binary tree structure.
 */
abstract class AbstractOrderIterator implements Iterator
{
    /** @var Node[] represents stack of nodes. */
    protected array $stack;
    /** @var Node|null current node in iteration. */
    protected ?Node $current;
    /** @var Node|null root node of the traversed tree. */
    protected ?Node $root;

    /**
     * @param Node|null $root root node of the tree structure to traverse.
     */
    public function __construct(?Node $root)
    {
        $this->stack = array();
        $this->root = $root;
        $this->current = $root;

        $this->rewind();
    }

    abstract public function rewind(): void;

    abstract public function next(): void;

    public function current(): ?Node
    {
        if (!$this->valid())
            throw new OutOfBoundsException();
        return $this->current;
    }

    public function key(): bool|int|float|string|null
    {
        $current = $this->current();
        return $current->getValue();
    }

    public function valid(): bool
    {
        return !is_null($this->current);
    }

    /**
     * @param Node $node parent node.
     * @return bool true if right child is not null.
     */
    protected function hasRightChild(Node $node): bool
    {
        return !is_null($node->getRight());
    }

    /**
     * @param Node $node parent node.
     * @return bool true if right child is not null.
     */
    protected function hasLeftChild(Node $node): bool
    {
        return !is_null($node->getLeft());
    }

    /**
     * Clear all data used to remember current position. Does not set current to root.
     */
    protected function clear(): void
    {
        unset($this->stack);
        $this->stack = array();
    }

}
