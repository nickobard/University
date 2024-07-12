#include <thread>
#include <iostream>
#include<unistd.h>
using namespace std;

string gLine;

void Echo(){
  while ( gLine != "stop"){

    getline(cin, gLine);
    cout << gLine << endl;;
  }
  cout << "Thred input done!" << endl;
}

int main () {

  thread t1 (Echo);

  while(gLine != "stop"){

  cout << "Update" << endl;
  sleep(1);
  }

  t1.join();

  return 0;
}