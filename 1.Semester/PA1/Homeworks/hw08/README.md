## Employee List

The task is to implement a set of functions for working with linked lists. The linked list represents a list of employees in a company. Each employee is represented by a name and a reference to their deputy. With such a list of employees, we want to perform the following operations: adding an employee, copying the list, and deleting the list.

**TEMPLOYEE**
This data structure is declared in the testing environment. Your implementation will work with this structure but must not alter it. The structure represents an employee. Employees are stored in the form of a singly linked list. The structure has the following components:
- `m_Next` - a link to the next employee in the linked list. The last employee in the list has this link set to NULL.
- `m_Bak` - a link to an employee's deputy. The link is either NULL (no deputy exists), or it points to some element of the linked list. In extreme cases, it may point to itself if, for cost-saving reasons, an employee is their own deputy.
- `m_Name` - an ASCIIZ (null-terminated) string indicating the employee's name.

**newEmployee (name, next)**
This function creates a new element in the linked list and places it at the first position. Parameters are `name` - the name of the new employee, and `next` - a link to the current beginning of the employee linked list. The return value of the function is a pointer to the first element of the new employee linked list. The function is responsible for allocating the employee structure and filling its components. The newly added employee does not have a defined deputy, so the `m_Bak` component will have a value of NULL.

**freeList (list)**
This function releases resources allocated in the employee linked list. The parameter of the function is a reference to the first element of the linked list of employees previously created using the `newEmployee` function.

**cloneList (list)**
This function creates a copy of the employee linked list. The newly created list must retain the employees' names, their order in the list, and must correctly adjust links to deputies. Note, the newly created list must be completely independent of the original, so even links to deputies must point to elements of the newly created list. The return value of the function is a reference to the first element of the copied list.

Submit the source file containing the implementation of the required functions. Add your other supporting functions called from these functions to the source file. Implemented functions will be called from the testing environment, so it is crucial to precisely follow the specified function interfaces. Use the code from the attached file as a basis for implementation. The code lacks the implementation of the required function bodies (and any other supporting functions). The example includes a test function `main`, the values provided are used in the basic test. Note that the inclusion of header files and the function `main` are wrapped in a conditional compilation block (#ifdef/#endif). Please keep these conditional compilation blocks in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the function `main` and the inclusion of header files "disappear," thus will not conflict with the header files and the `main` function of the testing environment.

Your program will be run in a restricted testing environment. It is limited by runtime (the limit is visible in the log of the reference solution) and also by the size of available memory. A sensible implementation of a naive algorithm should pass all tests except the speed test. To pass the speed test, a more powerful algorithm is needed that efficiently copies lists.

**Hint:**
- Use the source code from the attached file as the basis for your solution.
- You can add more of your tests to the function `main`, or you can change it freely. It is important to maintain conditional compilation.
- The example uses the `assert` macro. If the parameter is a non-zero value, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. If your implementation passes the example tests, the program will run and display nothing.
- Nothing is generally known about the names of the employees. Thus, names may, but do not have to be, unique.
- The solution to this task cannot be used for code review.
