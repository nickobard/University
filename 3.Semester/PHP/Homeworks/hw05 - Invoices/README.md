# Task 5: Invoices

The goal is to create a program that generates invoices as PDF documents. You have a skeleton application prepared with classes representing items on the invoice and a `Builder` class used for invoice creation. Use Composer to install the [DomPDF library](https://github.com/dompdf/dompdf). If for any reason you wish to use a different library, it's possible after discussing with your instructor.

Complete the missing parts of the `Invoice\Item`, `Builder`, and `Invoice` classes.

Additionally, implement the `Renderer` class to generate a PDF invoice. You can test using the `run.php` script:

```shell
$ php run.php > invoice.pdf
```


If you cannot open the PDF and do not see any errors, try running the program without redirecting the output - the error is likely being output instead of going to `invoice.pdf`.

```shell
$ php run.php
```


The `template.pdf` file shows how the final invoice should look. Your task is to use the DomPDF library to closely match this example. Refer to the library documentation to learn how to use it. There's no need to address Czech character support.

The point breakdown for each part is as follows:

- Installation of the DomPDF library and production of an openable PDF file **[1 point]**
- Invoice contains all required data **[2 points]**
- Invoice appearance:
  - Seller and buyer with appropriate formatting (phone number and email displayed only if set) **[1 point]**
  - Items table (correct framing, bold header and total row, alignment) **[1.5 points]**
  - Price formatting to two decimal places, decimal comma, thousands separated by space **[0.5 points]**

_If desired, you can use a favorite template system (for inspiration, see [here](https://ourcodeworld.com/articles/read/847/top-7-best-open-source-php-template-engines)), or learn a new one. However, it's not necessary for full completion of the task._
