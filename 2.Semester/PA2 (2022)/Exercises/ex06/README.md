## Set Implementation Using a Linked List

Your task is to implement the CLinkedSet class, which will represent the abstract data type "set" implemented using a sorted linked list. This implementation is particularly advantageous for operations such as union, intersection, and difference. You are required to implement only the basic operations, fulfilling the following interface:

- **Default Constructor**
  - Initializes an empty set.
  
- **Copy Constructor**
  - Creates a deep copy of an existing set.
  
- **Assignment Operator**
  - Deletes the current set and creates a deep copy of the given set.
  
- **Destructor**
  - Frees allocated resources.
  
- **bool Insert(const char * value)**
  - Inserts a string into the set, returns true if the insertion is successful. If the string is already in the set, the function returns false and does not change the set.
  
- **bool Remove(const char * value)**
  - Removes a string from the set, returns true if the removal is successful. If the string is not in the set, the function returns false and does not change the set.
  
- **bool Empty() const**
  - Returns true if the set is empty, otherwise false.
  
- **size_t Size() const**
  - Returns the number of elements in the set.
  
- **bool Contains(const char * value)**
  - Returns true if the string is in the set, otherwise false.

Strings are stored in the list in ascending order; use the `strcmp` function for comparison.

For implementation, use the CNode structure, which represents an element in the linked list, and implement the Value function that returns the string.

The attribute `m_Begin` must point to the first element of the linked list, and the last element must point to nullptr. The testing environment checks the structure of your linked list.

**Hints:**
- A solution that correctly implements a deep copy will score full points.
- You can add additional attributes and methods to the CLinkedSet and CNode classes. However, the testing environment relies on `m_Begin` pointing to the beginning of the linked list, `m_Next` being used as a pointer to the following element, and the Value function returning the string at the given position.
- Do not implement a linked list with a sentinel node. (For an empty linked list, `m_Begin` must be nullptr. For a linked list with one element, `m_Begin -> m_Next` must be nullptr, etc.)
- If your program fails to compile, make sure you are adhering to the specified interface.
