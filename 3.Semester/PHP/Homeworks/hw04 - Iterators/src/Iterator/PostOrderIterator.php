<?php declare(strict_types=1);

namespace Iterator;

use Node;

/**
 * Represents iterator over binary tree structure using post-order algorithm.
 */
class PostOrderIterator extends AbstractOrderIterator
{

    /** @var bool[] stores which nodes are expanded, saving them in parallel with nodes stack. */
    protected array $expandedNodes;

    public function __construct(?Node $root)
    {
        parent::__construct($root);
        $this->expandedNodes = array();
    }

    public function rewind(): void
    {
        $this->clear();
        if (is_null($this->root))
            return;

        $this->stack[] = $this->root;
        $this->expandedNodes[] = false;
        $this->expandNodes();
        $this->popLast();
    }

    public function next(): void
    {
        if (count($this->stack) !== 0) {
            $this->expandNodes();
            $this->popLast();
        } else {
            $this->current = null;
        }
    }

    /**
     * Expands last node, if is unexpanded to right and left.
     * Does it until top element in stack is expanded.
     * While expanding adds firstly right child if exists and then left child if exists to the stack.
     * Because they are new, sets them as unexpanded, so in next iteration the left child, if was present,
     * is expanding further, otherwise the right child is expanding, if was present.
     * Expanding stops when top node is a list.
     * @return void
     */
    protected function expandNodes(): void
    {
        while (!$this->isLastNodeExpanded()) {
            $this->expandLastNode();
            $expandedNode = $this->getTopNode();
            if (!is_null($expandedNode->getRight())) {
                $this->stack[] = $expandedNode->getRight();
                $this->expandedNodes[] = false;
            }
            if (!is_null($expandedNode->getLeft())) {
                $this->stack[] = $expandedNode->getLeft();
                $this->expandedNodes[] = false;
            }

        }
    }

    protected function clear(): void
    {
        parent::clear();
        unset($this->expandedNodes);
        $this->expandedNodes = array();
    }

    /**
     * Return top node from the stack.
     * Doesn't check for null.
     * @return Node from top of the stack.
     */
    private function getTopNode(): Node
    {
        return $this->stack[array_key_last($this->stack)];
    }

    /**
     * Set top node as expanded.
     * @return void
     */
    private function expandLastNode(): void
    {
        $this->expandedNodes[array_key_last($this->expandedNodes)] = true;
    }

    /**
     * @return bool true if top node is already expanded.
     */
    private function isLastNodeExpanded(): bool
    {
        return $this->expandedNodes[array_key_last($this->expandedNodes)];
    }

    /**
     * Pops top node and top expanded.
     * @return void
     */
    private function popLast(): void
    {
        $this->current = array_pop($this->stack);
        array_pop($this->expandedNodes);
    }

}
