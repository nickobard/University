#include <iostream>
using namespace std;

/*
 * Program to calculate recursively factorial of the number n
 */

int g_RecursionsNumber;

long long int fact (long long int num){
    g_RecursionsNumber ++ ;
    if ( num <= 1)
        return  1;
    else
        return num * fact ( num - 1 );
}

int main (){

    long long int num = 0;

    cout << "Choose your num to factorize:" << endl;
    
    while ( cin >> num ){
        if (num < 0){
            cout << "Negative number, try again." << endl;
            continue;
        }
        g_RecursionsNumber = 0;
        cout << num << "! = "
             << fact(num) << endl;
        cout << "Number of recursions: "
             << g_RecursionsNumber << endl;
    }
    return  0;
}