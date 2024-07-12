# Memory Manager

The given task focuses on understanding memory allocation in an OS. It involves implementing a simple manager for dynamically allocated memory of a user process.

In a simplified model environment, there is no heap manager (in the test environment on Progtest, it is disconnected). Therefore, functions like `malloc`, `free`, ..., or operators `new` and `delete` do not exist. Your task is to implement their simplified equivalents.

Your interface will operate over a block of entrusted memory of a given size (during initialization, you will be given a pointer to an existing memory block and information about the size of this memory block). The entrusted memory block will be contiguous and relatively large (units to hundreds of MiB). Your implemented memory subsystem will manage this entrusted memory block. This means enabling its use in smaller parts according to incoming requests, keeping track of allocated and unused parts of the entrusted memory block, enabling block allocation, releasing allocated blocks, and merging freed blocks into contiguous units.

You will submit the source code containing the functions with the specified interface. The test environment will attach your submitted source code and start using the functions from the defined interface. Based on their response, it will decide on the functionality or non-functionality of the submitted implementation. Therefore, it is necessary to strictly follow the interface specification (function names, parameter types, ...). The submitted code will not be a full-fledged program. For example, it will not have a main function; it will be more of a module (function library).

## Required Functions and Their Meaning:

### `int HeapInit (void * startAddr, int size);`
The `HeapInit` function will be called at the beginning during subsystem initialization, before calling other implemented functions. The function has a parameter `startAddr`, which specifies the memory address of the block your memory subsystem will manage. The second parameter is `size` - the size of the entrusted memory block in bytes.

In this memory block (starting at the address `startAddr` and having a size of `size` bytes), the heap will be implemented. All allocated blocks and your service information about how the parts of your heap are used/free will be stored here.

### `void HeapDone (int * pendingBlk);`
The `HeapDone` function will be called at the end of heap usage. The function will determine how many memory blocks are still allocated on the heap and pass this information to the caller through the output parameter `pendingBlk`.

### `void * HeapAlloc (int size);`
The `HeapAlloc` function will serve as an entry point for allocating a memory block in the managed heap. The function has a parameter specifying the size of the requested block and returns a pointer to the allocated memory space. If the function fails, it returns `NULL`. Failure can occur if the space in the entrusted memory is already exhausted or if the entrusted memory block, after previous allocations, no longer contains a sufficiently large contiguous space for the requested allocation.

### `bool HeapFree (void * blk);`
The `HeapFree` function serves to free a block previously allocated using `HeapAlloc`. The function returns `true` if the block was successfully freed, or `false` if the block could not be freed (invalid address given, block already freed, ...).

Submit a file that contains the implementation of the required functions, necessary declarations of global variables, data types, and support functions. Use the provided sample code as a base. If you keep the conditional compilation directives, the source file can be directly submitted to Progtest.

## Implementation Constraints:

- You have very limited resources (see the list of header files). STL is not available, and neither are standard functions for dynamic allocation (`malloc`, ...) nor their C++ equivalents (`new`). The submitted code will be run in a limited environment. You will be restricted by the available memory (besides the entrusted memory block, only a few kilobytes are available for storing a few global variables). This extra available memory is not sufficient to store all the service information about allocations (you will have to store this information in the managed memory and control its placement).

## Evaluation:

Evaluation is divided into mandatory and optional parts. In the mandatory part, the correctness of the allocator is tested. It must correctly allocate memory, ensure allocated blocks do not overlap, and properly merge freed memory.

Optional tests check how your implementation handles fragmentation and how quickly it can work for a large number of allocated blocks. If you fail these tests, your evaluation will be reduced.
