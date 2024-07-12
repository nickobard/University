TEST PROGES TEST (╬▔皿▔)╯

## E-Masks v2.1

While the reimplemented e-Mask has somewhat improved the situation with the spread of the epidemic, there is still a long way to go until it is under control. Therefore, it is necessary to expand this implementation to enable various simulations, predict future developments, and try to proactively respond to these developments with further measures. As the certified architects of the state information systems are still busy preparing to receive their well-deserved state honors, the responsibility for this project once again falls on you.

Your task is to implement three classes. You will need to design their interfaces yourself, and you will also need to adapt the interface to the intended use (see attached archive). The required classes are:

**CTimeStamp**, this class will implement a simple encapsulation of a timestamp. It must have a constructor that initializes its components (year, month, day, hour, minute, second). You can rely on being provided only valid date and time values.

**CContact** is a class that encapsulates a single contact between two users. Users are identified by their phone number, and the moment of contact is recorded in the form of a timestamp, **CTimeStamp**.

**CEFaceMask** is described in more detail below.
You may reuse the implementation of the first two classes from your solution to a previous exercise.

The last required class, **CEFaceMask**, must implement the following methods:

- **addContact** adds a record of a meeting between two individuals at a specified time to the database.
- **getSuperSpreaders** takes a time interval as a parameter and returns which of the monitored individuals could have infected the most other people in this interval (only direct contact is counted). There may be more than one such individual, so return a list of their phone numbers. If no contact occurred during the interval, return an empty list.

For the purposes of this task, represent telephone numbers as integers (in practice, this would not be a good idea as initial zeros are significant in phone numbers).

The return value of the **getSuperSpreaders** method represents a list of telephone numbers. The list must contain only unique numbers and must be sorted in ascending order.

Finally, from the principle of database fulfillment, it sometimes happens that a contact with oneself is accidentally generated. Ignore such contact.

**Notes:**
- In the attached archive, you will find sample runs of the program and test inputs.
- Focus on a clean class design. You definitely don't want to make all member variables publicly accessible. Use the exercises to consult on your design.
- The interval from and to is inclusive, including these values.
