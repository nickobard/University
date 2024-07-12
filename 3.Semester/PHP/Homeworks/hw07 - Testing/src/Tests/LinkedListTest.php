<?php

use HW\Lib\LinkedList;
use PHPUnit\Framework\TestCase;

/** @covers \HW\Lib\LinkedList */
class LinkedListTest extends TestCase
{

    protected LinkedList $list;

    public function setUp(): void
    {
        parent::setUp();
        $this->list = new LinkedList();
    }

    public function testShouldHaveCorrectStructureAfterAppendingList(): void
    {
        $this->assertSame(null, $this->list->getFirst());
        $this->assertSame(null, $this->list->getLast());

        $this->list->appendList("test");
        $this->list->appendList("progtest");
        $this->list->appendList("test");


        $this->assertSame("test", $this->list->getFirst()->getValue());
        $this->assertSame("test", $this->list->getLast()->getValue());
        $this->assertSame(null, $this->list->getFirst()->getPrev());
        $this->assertSame(null, $this->list->getLast()->getNext());
        $this->assertSame("progtest", $this->list->getFirst()->getNext()->getValue());
        $this->assertSame("progtest", $this->list->getLast()->getPrev()->getValue());

        $this->assertSame("test", $this->list
            ->getFirst()
            ->getNext()
            ->getNext()
            ->getValue());
        $this->assertSame("test", $this->list
            ->getLast()
            ->getPrev()
            ->getPrev()
            ->getValue());

    }

    public function testShouldHaveCorrectStructureAfterPrependingList(): void
    {
        $this->assertSame(null, $this->list->getFirst());
        $this->assertSame(null, $this->list->getLast());

        $this->list->prependList("test");
        $this->list->prependList("progtest");
        $this->list->prependList("test");


        $this->assertSame("test", $this->list->getFirst()->getValue());
        $this->assertSame("test", $this->list->getLast()->getValue());
        $this->assertSame(null, $this->list->getFirst()->getPrev());
        $this->assertSame(null, $this->list->getLast()->getNext());
        $this->assertSame("progtest", $this->list->getFirst()->getNext()->getValue());
        $this->assertSame("progtest", $this->list->getLast()->getPrev()->getValue());

        $this->assertSame("test", $this->list
            ->getFirst()
            ->getNext()
            ->getNext()
            ->getValue());
        $this->assertSame("test", $this->list
            ->getLast()
            ->getPrev()
            ->getPrev()
            ->getValue());

    }

    public function testShouldHaveCorrectStructureAfterPrependingAndAppendingList(): void
    {
        $this->assertSame(null, $this->list->getFirst());
        $this->assertSame(null, $this->list->getLast());

        $this->list->prependList("progtest");
        $this->list->appendList("test");
        $this->list->prependList("test");


        $this->assertSame("test", $this->list->getFirst()->getValue());
        $this->assertSame("test", $this->list->getLast()->getValue());
        $this->assertSame(null, $this->list->getFirst()->getPrev());
        $this->assertSame(null, $this->list->getLast()->getNext());
        $this->assertSame("progtest", $this->list->getFirst()->getNext()->getValue());
        $this->assertSame("progtest", $this->list->getLast()->getPrev()->getValue());

        $this->assertSame("test", $this->list
            ->getFirst()
            ->getNext()
            ->getNext()
            ->getValue());
        $this->assertSame("test", $this->list
            ->getLast()
            ->getPrev()
            ->getPrev()
            ->getValue());

    }


    public function testAppendingItem(): void
    {
        $this->assertSame(null, $this->list->getFirst());
        $this->assertSame(null, $this->list->getLast());

        $this->list->appendList("test");
        $this->list->appendList("test");
        $this->list->appendItem($this->list->getFirst(), "progtest");


        $this->assertSame("test", $this->list->getFirst()->getValue());
        $this->assertSame("test", $this->list->getLast()->getValue());
        $this->assertSame(null, $this->list->getFirst()->getPrev());
        $this->assertSame(null, $this->list->getLast()->getNext());
        $this->assertSame("progtest", $this->list->getFirst()->getNext()->getValue());
        $this->assertSame("progtest", $this->list->getLast()->getPrev()->getValue());


        $this->assertSame("test", $this->list
            ->getFirst()
            ->getNext()
            ->getNext()
            ->getValue());
        $this->assertSame("test", $this->list
            ->getLast()
            ->getPrev()
            ->getPrev()
            ->getValue());
    }

    public function testPrependingItem(): void
    {
        $this->assertSame(null, $this->list->getFirst());
        $this->assertSame(null, $this->list->getLast());

        $this->list->appendList("test");
        $this->list->appendList("test");
        $this->list->prependItem($this->list->getLast(), "progtest");


        $this->assertSame("test", $this->list->getFirst()->getValue());
        $this->assertSame("test", $this->list->getLast()->getValue());
        $this->assertSame(null, $this->list->getFirst()->getPrev());
        $this->assertSame(null, $this->list->getLast()->getNext());
        $this->assertSame("progtest", $this->list->getFirst()->getNext()->getValue());
        $this->assertSame("progtest", $this->list->getLast()->getPrev()->getValue());


        $this->assertSame("test", $this->list
            ->getFirst()
            ->getNext()
            ->getNext()
            ->getValue());
        $this->assertSame("test", $this->list
            ->getLast()
            ->getPrev()
            ->getPrev()
            ->getValue());
    }


}