#include <iostream>
using namespace std;
constexpr int ARR_MAX = 12;
int g_Cnt;
/**
 * Program to find max in an array recursively
 */

int max(int arr[], int len ){
  g_Cnt++;
  if (len == 1)
    return *arr;
  int tmp = max(arr + 1, len - 1);
  return *arr > tmp ? *arr : tmp;
}

int main (){
  int arr1[ARR_MAX] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int arr2[ARR_MAX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  g_Cnt = 0;
  cout << "Arr1: Max = " << max(arr1,ARR_MAX) << "; g_Cnt = " << g_Cnt << endl;
  g_Cnt = 0;
  cout << "Arr2: Max = " << max(arr2,ARR_MAX) << "; g_Cnt = " << g_Cnt << endl;
  return 0;
}