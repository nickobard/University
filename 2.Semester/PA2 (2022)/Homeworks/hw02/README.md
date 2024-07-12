## VAT Reporting System Implementation

Your task is to implement the CVATRegister class, which will manage a database of VAT control statements. This system is introduced to more rigorously combat tax evasion. The database will record individual companies and the invoices issued by them. Companies can be added to and removed from the database. A company is identified by its name, address, and tax identifier (id). The tax identifier is unique across the entire database. While names and addresses may repeat, the combination of (name, address) is unique in the database. For example, there can be many companies named ACME, many companies can have the address "Prague," but there can only be one ACME residing in Prague. When comparing tax identifiers, case sensitivity is observed; however, names and addresses are case insensitive.

The public interface is listed below:

- **Constructor**
  - This constructor initializes an instance of the class so that the resulting instance does not yet contain any records.

- **Destructor**
  - Frees resources allocated by the instance.

- **bool newCompany(name, addr, id)**
  - Adds another record to the existing database. Parameters `name` and `addr` represent the company's name and address, respectively, while `id` specifies the tax identifier. The method returns `true` if the record was added, or `false` if it was not added because a record with the same name and address or the same id already exists in the database.

- **bool cancelCompany(name, addr)** / **bool cancelCompany(id)**
  - Removes a record from the database. The parameter uniquely identifies the company either by name and address (first variant) or by tax identifier (second variant). If the record was actually removed, the method returns `true`. If the record does not remove (because no company with this identification existed), the method returns `false`.

- **bool invoice(name, addr, amount)** / **bool invoice(id, amount)**
  - Records an income of `amount`. There are two variants: either the company is identified by its name and address or by the tax identifier. If the method succeeds, it returns `true`; if it fails, it returns `false` (non-existent company).

- **bool audit(name, addr, sum)** / **bool audit(id, sum)**
  - Searches for the total income for a company identified by either name and address or by the tax identifier. The found total is stored in the output parameter `sum`. The method returns `true` for success and `false` for failure (non-existent company).

- **medianInvoice()**
  - Searches for the median invoice value. All successfully processed invoices submitted by calling invoice are included in the calculation. Invoices that could not be assigned (failed invoice calls) are not counted, but all registered invoices are counted, so when a company is deleted, its invoices are not removed from the median calculation. If there is an even number of invoices in the system, the higher of the two middle values is taken. If no invoice has been processed yet, a value of 0 is returned.

- **firstCompany(name, addr)** / **nextCompany(name, addr)**
  - Used to traverse the existing list of companies in our database. Companies are traversed in alphabetical order by their name. If two companies have the same name, their address decides the order. The `firstCompany` method finds the first company. If the list of companies is empty, the method returns `false`. Otherwise, it returns `true` and fills the output parameters `name` and `addr`. The `nextCompany` method works similarly; it finds the next company in the list following the company identified by the parameters. If there is no next company after `name` and `addr` in the list, the method returns `false`. Otherwise, the method returns `true` and overwrites the parameters `name` and `addr` with the name and address of the next company.

**Submission Requirements:**
- Submit a file that contains your implemented CVATRegister class. The class must meet the public interface as described - if your submitted solution does not contain the described interface, a compilation error will occur. You may add additional methods (public or private) and member variables to the class. The submitted file must contain both the declaration of the class (interface description) and the definitions of methods, constructors, and destructors. It does not matter whether the methods are implemented inline or separately. The submitted file must not contain anything other than the implementation of the CVATRegister class, especially not the insertion of header files and the `main` function (the function `main` and the insertion of header files may remain but only wrapped in conditional compilation directives). Use the attached source file as the basis for implementation.

**Testing Environment:**
- The class is tested in a limited environment where available memory is restricted (sufficient for storing the list) and runtime is limited. The implemented class does not have to deal with a copy constructor or the overloading of the assignment operator. In this task, ProgTest does not perform tests of this functionality.

**Efficiency:**
- The implementation of the class must be efficient in terms of time and memory requirements. A simple linear solution is insufficient (for test data it requires more than 5 minutes). Assume that creating and destroying a company are infrequent compared
