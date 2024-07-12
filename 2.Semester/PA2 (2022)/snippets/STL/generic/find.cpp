#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main (){
cout << "Vector: " << endl;
vector<int> vec1 = {1,2,3,4,5,6,7,8,9,10,0}; //11 elements
int val = 42; // value we are looking for
auto ret = find(vec1.cbegin(), vec1.cend(), val);  
// the reurn type is the iterator to that element, noo the boolean.
// remember - these algorithms are generic, we may use them for many
// situations. Iterator return type is more universal solution.
cout << "The value " << val 
     << ( ret == vec1.cend()
            ? " is not present" : " is present") << endl;

// there are also begin() and end() functions. So we can use them to create iterators in the array (sequential)
// or not?
cout << "Array: " << endl;
int ia[] = {1,2,3,4,5,6,7,8,9,10,0};

// the return type of the begin() and end() are int * - pointers!
int * result1 = find(begin(ia), end(ia), val);
cout << "The value " << val 
     << ( result1 == end(ia) // we should use again end.
            ? " is not present" : " is present") << endl;

int * result2 = find(ia, ia + sizeof(ia)/sizeof(*ia), val);
// the sizeof(ia)/sizeof(*a) will return the size of the array
cout << "The value " << val 
     << ( result2 == end(ia) // we should use again end.
            ? " is not present" : " is present") << endl; 

int arr[] = {1,2,3}; // 3 elements
cout << *begin(arr) << endl;
cout << *(end(arr) - 1) << endl; // the end returns pointer to off-the-end element. So it is compatible with iterators and share same behaviour

// invalid, because is equivalent ot ia[11], when we have only 11 elements.
//cout << *(ia + sizeof(ia)/sizeof(*ia)) << endl; // segfault


// we can find in the subset of the array (or called subrange)
cout << "Last one!" << endl;
int * result3 = find (ia + 3,ia + 5, val);
  return 0;
cout << "The value " << val 
     << ( result3 == end(ia) // we should use again end.
            ? " is not present" : " is present") << endl; 
// very interesting, that if not found, it returns the end of the whole array, not of the specific subrange

}