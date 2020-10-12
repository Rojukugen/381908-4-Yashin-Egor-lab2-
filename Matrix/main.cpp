#include <iostream>
#include "MyVector.h"
#include "Matrix.h"
int main()
{
  TMatrix<int> A(3);
  TMatrix<int> B = A;
  TMatrix<int> C(3);
  C = A + B;
  cout << C << endl;
  return 0;
}
