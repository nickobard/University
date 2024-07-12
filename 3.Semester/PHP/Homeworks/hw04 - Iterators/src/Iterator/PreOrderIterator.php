<?php declare(strict_types=1);

namespace Iterator;

use Node;

/**
 * Represents iterator over binary tree structure using pre-order algorithm.
 */
class PreOrderIterator extends AbstractOrderIterator
{
    public function rewind(): void
    {
        $this->clear();
        if (is_null($this->root))
            return;
        $this->current = $this->root;
        $this->addChildrenToStack($this->root);
    }

    public function next(): void
    {
        $this->current = array_pop($this->stack);
        if (!is_null($this->current))
            $this->addChildrenToStack($this->current);
    }

    protected function addChildrenToStack(Node $node): void
    {
        if ($this->hasRightChild($node))
            $this->stack[] = $node->getRight();
        if ($this->hasLeftChild($node))
            $this->stack[] = $node->getLeft();
    }
}
