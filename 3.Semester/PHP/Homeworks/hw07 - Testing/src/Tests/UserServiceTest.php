<?php declare(strict_types=1);

namespace HW\Tests;

use Exception;
use http\Client\Curl\User;
use HW\Lib\Storage;
use HW\Lib\UserService;
use JsonException;
use PHPUnit\Framework\TestCase;

/** @covers \HW\Lib\UserService */
class UserServiceTest extends TestCase
{
    private Storage $storage;
    protected UserService $userService;

    /** @inheritDoc */
    protected function setUp(): void
    {
        $this->storage = $this->createMock(Storage::class);
        $this->userService = new UserService($this->storage);
    }

    public function testShouldCreateUserService(): void
    {
        $storage = $this->createStub(Storage::class);
        $userService = new UserService($storage);
        $this->assertNotNull($userService);
    }

    public function testShouldCreateUserAndReturnSomeId(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('save')
            ->with(
                $this->isType('string'),
                $this->isType('string')
            );
        try {
            $this->userService->createUser("dummy", "dummy@dummy.dummy");
        } catch (Exception $e) {
            $this->fail("Should not throw exception.");
        }
    }

    public function testShouldReturnValidUsername(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('{ "username" : "dummy", "email" : "dummy@dummy" }');
        try {
            $this->assertSame("dummy", $this->userService->getUsername("42"));
        } catch (Exception $e) {
            $this->fail("Should not throw exception");
        }
    }

    public function testShouldNotReturnValidUsername(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('{ "username" : "dummy", "email" : "dummy@dummy" }');
        try {
            $this->assertNotEquals("NAD - Not a Dummy", $this->userService->getUsername("42"));
        } catch (Exception $e) {
            $this->fail("Should not throw exception");
        }
    }


    public function testShouldThrowJsonExceptionGettingWrongUserDataUsername(): void
    {
        $this->expectException(JsonException::class);
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('wrong json format, sorry');
        $this->assertNotEquals("NAD - Not a Dummy", $this->userService->getUsername("42"));
    }

    public function testShouldReturnNullWhenTryToGetUsernameWithNonExistentId(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn(false);
        $this->assertEquals(null, $this->userService->getUsername("42"));
    }

    public function testShouldReturnValidEmail(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('{ "username" : "dummy", "email" : "dummy@dummy" }');
        try {
            $this->assertSame("dummy@dummy", $this->userService->getEmail("42"));
        } catch (Exception $e) {
            $this->fail("Should not throw exception");
        }
    }

    public function testShouldNotReturnValidEmail(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('{ "username" : "dummy", "email" : "dummy@dummy" }');
        try {
            $this->assertNotEquals("NAD - Not a Dummy", $this->userService->getEmail("42"));
        } catch (Exception $e) {
            $this->fail("Should not throw exception");
        }
    }


    public function testShouldThrowJsonExceptionGettingWrongUserDataEmail(): void
    {
        $this->expectException(JsonException::class);
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn('wrong json format, sorry');
        $this->assertNotEquals("NAD - Not a Dummy", $this->userService->getEmail("42"));
    }

    public function testShouldReturnNullWhenTryToGetEmailWithNonExistentId(): void
    {
        $this->storage
            ->expects($this->once())
            ->method('get')
            ->with(
                $this->isType('string'),
            )
            ->willReturn(false);
        $this->assertEquals(null, $this->userService->getEmail("42"));
    }

}
