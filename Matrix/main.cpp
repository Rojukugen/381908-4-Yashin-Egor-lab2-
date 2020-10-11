#include <iostream>
#include "MyVector.h"
#include "Matrix.h"
int main()
{
  Vector<int> a(3, 3);
  TMatrix<int> A(3);
  TMatrix<int> B = A;
  TMatrix<int> C(3);
  C = A + B;
  return 0;
}
