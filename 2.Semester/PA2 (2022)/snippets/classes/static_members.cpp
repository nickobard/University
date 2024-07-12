#include <iostream>
using namespace std;


class Account{
  public:
    static void rate(double rate){
      interestRate = rate;
    }
    void printRate() {
      cout << interestRate << endl;
    }
  private:
    static double interestRate;
    static double initRate(){
      return 0;
    }
};
// should be in the .cpp file..
double Account::interestRate = Account::initRate();

int main(){
  Account ac1;
  ac1.rate(25);
  // ac1.printRate();
  
  return 0;
}