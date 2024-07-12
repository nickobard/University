#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class CBitArray {
  public:
  CBitArray &readBits (const char val){
    for ( unsigned char mask = 0b1000'0000; mask != 0; mask >>= 1){
      bitArr.push_back(mask & val);   
    }
    return *this;
  }
  void printBits() const {
    for ( const bool a : bitArr){
      cout << a;
    }
    cout << endl;
  }
  private:
  vector<bool> bitArr;
};

int main(){
	/*
	 * How to set value of int usin binary number representation.
	 */
	int x = 0b00000000'00000000'00000000'00000011; // 3
	int y = 0b1010; // 10
	cout << "val: x : " << x << endl;
	cout << "val: y : " << y << endl;
  
bool isRaining = true;
bool boolArr[2];
cout << sizeof(isRaining) << " bytes" << endl;
cout << sizeof(boolArr) << " bytes" << endl;

CBitArray bitArr;
char a = (char) 0b10101010;
bitArr.readBits(a).readBits(a).printBits();
	return 0;
}	