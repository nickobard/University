<?php declare(strict_types=1);

namespace Iterator;

use Node;

/**
 * Represents iterator over binary tree structure using in-order algorithm.
 */
class InOrderIterator extends AbstractOrderIterator
{

    public function next(): void
    {
        if (!$this->valid())
            return;
        if ($this->hasRightChild($this->current)) {
            $this->current = $this->current->getRight();
            $this->goLeft();
        } else if (count($this->stack) !== 0)
            $this->current = array_pop($this->stack);
        else
            $this->current = null;
    }

    public function rewind(): void
    {
        $this->clear();
        if (is_null($this->root))
            return;
        $this->current = $this->root;
        $this->goLeft();
    }

    /**
     * Set current to the most left node down the tree until node doesn't have left child.
     */
    private function goLeft(): void
    {
        while (!is_null($this->current->getLeft())) {
            $this->stack[] = $this->current;
            $this->current = $this->current->getLeft();
        }
    }
}
