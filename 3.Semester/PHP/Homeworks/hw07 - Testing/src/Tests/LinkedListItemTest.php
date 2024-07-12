<?php declare(strict_types=1);

namespace HW\Tests;

use HW\Lib\LinkedListItem;
use PHPUnit\Framework\TestCase;


/** @covers \HW\Lib\LinkedListItem */
class LinkedListItemTest extends TestCase
{
    public function testLinkedListItemConstructor(): void
    {
        $item = new LinkedListItem("dummy");
        $this->assertSame(null, $item->getPrev());
        $this->assertSame(null, $item->getNext());
        $this->assertSame("dummy", $item->getValue());
    }

    public function testChangingValueInTheListItem(): void
    {
        $item = new LinkedListItem("dummy");
        $this->assertSame("dummy", $item->getValue());
        $item->setValue("NAD");
        $this->assertNotSame("dummy", $item->getValue());
        $this->assertSame("NAD", $item->getValue());
    }

    public function testLinkedListNextAndPreviousSet(): void
    {
        $item = new LinkedListItem("dummy");
        $next = new LinkedListItem("next dummy");
        $prev = new LinkedListItem("prev dummy");

        $item->setPrev($prev);
        $item->setNext($next);

        $this->assertSame("prev dummy", $item->getPrev()->getValue());
        $this->assertSame("next dummy", $item->getNext()->getValue());
        $this->assertSame("dummy", $item->getValue());
    }

}
