<?php declare(strict_types=1);

namespace App;

use App\Invoice\BusinessEntity;
use Dompdf\Dompdf;
use Dompdf\Options;

class Renderer extends Dompdf
{
    public function makeInvoice(Invoice $invoice): string
    {
        $dompdf = new Dompdf();
        $dompdf->loadHtml(
            str: <<<RENDER
        <!DOCTYPE html>
    <html lang="cz">
    <head>
        <meta charset="UTF-8">
        <title>Faktura</title>
        {$this->getStyle()}
    </head>
    <body>
    
    {$this->getTitle($invoice)}
    
    {$this->getDetailsTable($invoice)}<br>
    
    {$this->getItemsTable($invoice)}<br>
    
    </body>
    </html>
    RENDER
        );
        $dompdf->setPaper('A4');
        $dompdf->render();
        return $dompdf->output();
    }

    protected function getStyle(): string
    {
        return <<<STYLE
<style>
    body {
        font-family: Courier,serif;
    }
    table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
        font-family: Courier,serif;
    }
    table {
        width: 100%;
    }
    
</style>
STYLE;
    }

    protected function getTitle(Invoice $invoice): string
    {
        return <<<TITLE
<h3>FAKTURA - DOKLAD c. {$invoice->getNumber()}</h3>
TITLE;

    }

    protected function getDetailsTable(Invoice $invoice): string
    {
        return <<<TABLE
<table>
    <tr>
        <td style="width:50%">
            <b>Dodavatel</b>
            {$this->getBusinessEntityInfo($invoice->getSupplier())}
        </td>
        <td style="width: 50%">
            <b>Odberatel</b>
            {$this->getBusinessEntityInfo($invoice->getCustomer())}
        </td>
    </tr>    
</table>
TABLE;
    }

    protected function getBusinessEntityInfo(BusinessEntity $info): string
    {
        return <<<INFO
<p>
{$info->getName()}<br>
{$info->getAddress()->getStreet()} {$info->getAddress()->getNumber()}<br>
{$info->getAddress()->getZipCode()} {$info->getAddress()->getCity()}<br>
</p>
<p>
{$info->getVatNumber()}
</p>
<p>
{$this->getPhoneNumber($info)}<br>
{$this->getEmail($info)}<br>
</p>
INFO;

    }

    protected function getPhoneNumber(BusinessEntity $info): string
    {
        $phone_number = $info->getAddress()->getPhone();
        if (is_null($phone_number))
            return '';
        return $phone_number;
    }

    protected function getEmail(BusinessEntity $info): string
    {
        $email = $info->getAddress()->getEmail();
        if (is_null($email))
            return '';
        return $email;
    }

    protected function getItemsTable(Invoice $invoice): string
    {
        $items_rows = '';
        foreach ($invoice->getItems() as $item) {
            $items_rows .= <<<ROW
<tr>
    <td style="width: 25%">{$item->getDescription()}</td>
    <td align="right" style="text-align: right" style="width: 25%">{$this->formatNumber($item->getQuantity())}</td>
    <td align="right" style="text-align: right" style="width: 25%">{$this->formatNumber($item->getUnitPrice())}</td>
    <td align="right" style="text-align: right" style="width: 25%">{$this->formatNumber($item->getTotalPrice())}</td>
</tr>
ROW;
        }
        return <<<TABLE
<table>
    <tr>
        <td  style="width: 25%"><b>Polozka</b></td>
        <td  style="width: 25%"><b>Pocet m.j.</b></td>
        <td  style="width: 25%"><b>Cena za m.j.</b></td>
        <td  style="width: 25%"><b>Celkem</b></td>

    </tr>
    $items_rows
    <tr>
        <td style="width: 25%"><b>Celkem</b></td>
        <td align="right" colspan="3" style="width: 75%"><b>{$this->formatNumber($invoice->getTotalPrice())}</b></td>
    </tr>
</table>
TABLE;
    }

    protected function formatNumber(float|int $number): string
    {
        $number = (string)((int)($number * 100) / 100);
        $res = strpos($number, '.');
        if ($res === false) {
            $formatted = '';
            $count = 0;
            for ($i = strlen($number) - 1; $i >= 0; $i--) {
                $formatted .= $number[$i];
                $count += 1;
                if ($count % 3 === 0 && $count !== 0)
                    $formatted .= ' ';
            }
            return strrev($formatted);
        }

        $number[$res] = ',';
        $formatted = '';
        $count = 0;
        for ($i = $res - 1; $i >= 0; $i--) {
            $formatted .= $number[$i];
            $count += 1;
            if ($count % 3 === 0 && $count !== 0)
                $formatted .= ' ';
        }

        $formatted = strrev($formatted);
        for ($i = $res; $i < strlen($number); $i++) {
            $formatted .= $number[$i];
        }
        return $formatted;
    }
}
