## Versioned File

The task is to design and implement a class `CFile` that will simulate a binary file.

The required class will meet the interface as shown in the example below. The requirements include read and write operations, setting the pointer position, and truncating the file. Additionally, the class should be able to remember versions of the file. The interface includes a method to archive the current content of the file. Subsequently, it should be possible to revert to this version of the file. Many such versions can be created (limited only by the available memory), and it should be possible to revert to any older version (using the "undo" principle). It is assumed that the stored data is written to memory (not to disk, the class only simulates file behavior).

For backup reasons, we want to be able to create copies of an existing `CFile` instance. Copies will be created either by the copy constructor or the assignment operator. The resulting copies must be identical independent objects, meaning that operations on one cannot affect the contents of the other. On the other hand, it can be assumed that there will not be many changes between copies, so some data can be shared between copies to save space. Copying creates an identical object, meaning that stored versions of the content are also transferred.

### Required Class Interface

- **Constructor**: 
  - Default constructor creates an empty file instance (size 0 B, position in the file 0).
- **Destructor**, **Assignment Operator**, and **Copy Constructor**: 
  - Implement if the automatically generated versions are not suitable.
- **write(data, len)**: 
  - Method writes the given data block (`data`) of length `len` at the current position. The current position in the file moves to the last written byte after writing. The `write` method overwrites data (if the current position is inside the file) / extends the file size. The return value is the number of bytes written.
- **read(data, len)**: 
  - Method reads the requested number of bytes (`len`) into the array `data`. The return value is the number of bytes read (can be less than `len` depending on the current position in the file). The method also moves the current position in the file forward by the number of bytes read.
- **seek(pos)**: 
  - Method moves the current position in the file to the position `pos`. The position is used for subsequent read/write operations. The parameter `pos` must be within the range of 0 to the length of the file (both bounds inclusive). The return value is `true` for success, `false` for failure (position out of bounds).
- **truncate()**: 
  - Method truncates the file to the size given by the current position in the file.
- **fileSize()**: 
  - Method returns the current file size in bytes.
- **addVersion()**: 
  - Method archives the current file content and current position in the file (creates a version). This version is stored in the `CFile` instance.
- **undoVersion()**: 
  - Method reverts the file content and current position in the file to the state they were in during the corresponding previous `addVersion` call. It is possible to revert to previous versions multiple times as long as previous archived versions exist. Calling `undoVersion` returns `true` for success, `false` for failure (no previous version exists).

Submit a file that contains the implemented `CFile` class. The class must meet the public interface according to the example - if your submitted solution does not contain the described interface, a compilation error will occur. However, you can add other methods (public or private) and member variables to the class. The submitted file must contain both the class declaration (interface description) and the definitions of methods, constructor, and destructor. It does not matter whether the methods are implemented inline or separately. The submitted file must not contain any header file inclusions or the `main` function (the `main` function and header file inclusions can remain but only wrapped in conditional compilation directives as shown in the example below).

The class is tested in a restricted environment with limited available memory (sufficient to store the list) and limited runtime. For this solution, you intentionally do not have access to STL or `std::string`. The task aims to practice understanding deep and shallow copies. Using STL would not fulfill this goal.

The required public interface of the class and an example of usage are in the attached archive.

### Notes:
- Evaluation is divided between mandatory, optional, and bonus tests. To pass the mandatory tests, it is sufficient to implement the basic version of content copying.
- To pass further tests, it is necessary to efficiently share parts of the data so that the resulting copies occupy a reasonable amount of memory. You can assume that changes between versions and changes between instance copies are small. Therefore, immutable parts can be shared using reference counting and copy-on-write techniques.
- In the optional test, instances of `CFile` are copied and content versions are created, but the total number of different content versions is low. Therefore, it is sufficient to consider reference counting for entire content versions of files.
- In the bonus test, the files are intensively changed after copying and many different versions of the file are created. To save memory, it is necessary to involve reference counting and copy-on-write even for versions or parts of files.
- A solution that passes the mandatory and optional tests with 100% can be used for code review (passing the bonus test is not required for code review).
