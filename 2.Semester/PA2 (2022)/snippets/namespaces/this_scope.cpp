#include <iostream>
using namespace std;

void cout () {
  std::cout << "Hello world!" << endl;
}

int main () {
  ::cout();
  return 0;
}