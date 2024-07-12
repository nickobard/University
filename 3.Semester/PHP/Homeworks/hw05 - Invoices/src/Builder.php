<?php declare(strict_types=1);

namespace App;

use App\Invoice\Address;
use App\Invoice\BusinessEntity;
use App\Invoice\Item;

class Builder
{
    protected Invoice $invoice;

    public function __construct()
    {
        $this->invoice = new Invoice();
    }

    public function build(): Invoice
    {
        $invoice = $this->invoice;
        $this->invoice = new Invoice();
        return $invoice;
    }

    public function setNumber(string $number): self
    {
        $this->invoice->setNumber($number);
        return $this;
    }

    public function setSupplier(
        string  $name,
        string  $vatNumber,
        string  $street,
        string  $number,
        string  $city,
        string  $zip,
        ?string $phone = null,
        ?string $email = null
    ): self
    {

        $this->invoice->setSupplier((new BusinessEntity())
            ->setName($name)
            ->setVatNumber($vatNumber)
            ->setAddress((new Address())
                ->setStreet($street)
                ->setNumber($number)
                ->setCity($city)
                ->setZipCode($zip)
                ->setPhone($phone)
                ->setEmail($email)
            )
        );
        return $this;
    }

    public function setCustomer(
        string  $name,
        string  $vatNumber,
        string  $street,
        string  $number,
        string  $city,
        string  $zip,
        ?string $phone = null,
        ?string $email = null
    ): self
    {
        $this->invoice->setCustomer((new BusinessEntity())
            ->setName($name)
            ->setVatNumber($vatNumber)
            ->setAddress((new Address())
                ->setStreet($street)
                ->setNumber($number)
                ->setCity($city)
                ->setZipCode($zip)
                ->setPhone($phone)
                ->setEmail($email)
            )
        );
        return $this;
    }

    public function addItem(string $description, ?float $quantity, ?float $price): self
    {
        $this->invoice->addItem((new Item())
            ->setDescription($description)
            ->setQuantity($quantity)
            ->setUnitPrice($price)
        );
        return $this;
    }
}
