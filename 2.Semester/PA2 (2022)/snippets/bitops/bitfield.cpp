#include <iostream>
#include <vector>
using namespace std;
class CBitArray {
struct TBitField{
  unsigned char b1: 1;
  unsigned char b2: 1;
  unsigned char b3: 1;
  unsigned char b4: 1;
  unsigned char b5: 1;
  unsigned char b6: 1;
  unsigned char b7: 1;
  unsigned char b8: 1;
};
public:
void printBits () const {
  cout << "Bit fields:" << endl;
    cout << f1.b1
         << f1.b2
         << f1.b3
         << f1.b4
         << f1.b5
         << f1.b6
         << f1.b7
         << f1.b8 << endl;

}
CBitArray &readBits(const char a){
  unsigned char mask = (char) 0b1000'0000;
  if (mask & a) f1.b1 = 1; else f1.b1 = 0;
  mask >>= 1;
  if (mask & a) f1.b2 = 1; else f1.b2 = 0;
  mask >>= 1;
  if (mask & a) f1.b3 = 1; else f1.b3 = 0;
  mask >>= 1;
  if (mask & a) f1.b4 = 1; else f1.b4 = 0;
  mask >>= 1;
  if (mask & a) f1.b5 = 1; else f1.b5 = 0;
  mask >>= 1;
  if (mask & a) f1.b6 = 1; else f1.b6 = 0;
  mask >>= 1;
  if (mask & a) f1.b7 = 1; else f1.b7 = 0;
  mask >>= 1;
  if (mask & a) f1.b8 = 1; else f1.b8 = 0;
  return *this;
}
private:
  TBitField f1;
};

int main (){
  CBitArray bArr1;
  char x = (char) 0b10011001;
  // field1 = (TBitField) x; // error
  bArr1.readBits(x);
  bArr1.printBits(); // segfault anebo [][][][]

return 0;
}

// https://stackoverflow.com/questions/4240974/when-is-it-worthwhile-to-use-bit-fields?msclkid=a64f5767aacb11ecb7bb60eb89aed531