#pragma once
#include "MyVector.h"
template <class T>
class TMatrix :public Vector<Vector<T>>
{
public:
	TMatrix(int _size = 0);
	TMatrix(const TMatrix<T>& A);
	~TMatrix();
    TMatrix<T>& operator =(const TMatrix<T>& A);
	TMatrix<T> operator +(const TMatrix<T>& A);
};

template<class T>
inline TMatrix<T>::TMatrix(int _size) : Vector<Vector<T>> (_size)
{
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix<T>& A) : Vector<Vector<T>>(A)
{
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& A)
{
	if (this != &A)
	{
		Vector<Vector<T>>::operator = (A);
	}
	return *this;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& A)
{
	TMatrix<T> tmp (*this);
	for (int i = 0; i < this->length;i++)
		tmp.x[i] = tmp.x[i] + A.x[i];
	return tmp;
}




