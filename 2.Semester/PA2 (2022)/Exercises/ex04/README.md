## E-Masks

n light of COVID-19 spiraling out of control once more, more stringent measures are necessary. One of the steps includes the reimplementation of e-masks. Since the certified architects of the state information systems are busy preparing to receive their well-deserved state honors, you will not only have to implement the program this time but also design the appropriate interfaces.

Your task is to implement three classes. You will need to design their interfaces yourself, and you will need to adapt the interface to the anticipated use (see the attached archive). The required classes are:

**CTimeStamp**, this class will implement a simple encapsulation of a timestamp. It must have a constructor in which it initializes its components (year, month, day, hour, minute, second). You can rely on being provided only valid date and time values.

**CContact** is a class that encapsulates a single contact between two users. Users are identified by their phone number, and the moment of contact is recorded in the form of a timestamp, **CTimeStamp**.

**CEFaceMask** is a class that aggregates recorded contacts. Contacts are added using the method `addContact` (method calls can be chained), and the contacts are retrieved using the method `listContacts` (this method should not modify the object, so it should be const). The search method can be called with one parameter (the phone number of the infected person) or with three parameters (the phone number of the infected person, the start and end of the time interval). The method returns a list of numbers that the queried person was in contact with (in the second case, additionally within a defined time interval).

For the purposes of this task, represent telephone numbers as integers (in practice, this would not be a good idea as initial zeros are significant in phone numbers). The return values of the `listContacts` method will return a list of phone numbers of infected contacts. Ensure that the numbers do not repeat in the results, thus suppress the second and subsequent occurrences of the same number. Additionally, for tracing purposes, it's important that the phone numbers in the result are stored in the order they were entered (earlier entered contacts will appear earlier in the results). Finally, from the principle of database fulfillment, it sometimes happens that a contact with oneself is accidentally generated. Such a contact would unnecessarily confuse tracers, so do not add it to the results.

**Notes:**

- In the attached archive, you will find sample runs of the program and test inputs. (The inputs are correct; do not modify them, otherwise, your program will not compile on Progtest.)
- You do not need to deal with the efficiency of the solution; a reasonable implementation of naive algorithms is sufficient.
- Focus on clean class design. You definitely don't want to make all member variables public. Use the exercises for consulting your design.