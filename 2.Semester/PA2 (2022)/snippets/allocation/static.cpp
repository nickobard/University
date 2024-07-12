int main (){
  static int * iptr = new int;
  delete iptr;
  return 0;
}