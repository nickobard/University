#include <iostream>
#include <ctime>
using namespace std;

int main (){
  tm ttime {}; 
  ttime.tm_year = 2000 - 1900;
  ttime.tm_mon  = 1 - 1;
  ttime.tm_mday  = 1;
  cout << asctime(&ttime) << endl;
  ttime.tm_mday += 366;
  mktime(&ttime);
  cout << asctime(&ttime) << endl;
  ttime.tm_mday -= 366;
  mktime(&ttime);
  cout << asctime(&ttime) << endl;
  return 0;
}