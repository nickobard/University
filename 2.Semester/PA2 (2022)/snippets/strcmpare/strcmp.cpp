#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;
int main(){
    string a = "a";
    string b = "John Christescu";
    cout << a + " cmp " + b + " " << strcmp ("a", "John Christescu") << endl;
    cout << a + " > " + b + " " << boolalpha << (a > b) << endl;
    b = "b";
    cout << a + " > " + b + " " << boolalpha << (a > b) << endl;
    b = "A";
    cout << a + " > " + b + " " <<  boolalpha << (a > b) << endl;

    return 0;
}