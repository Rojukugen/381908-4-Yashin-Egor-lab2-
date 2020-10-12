#pragma once
#include "MyVector.h"

template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s);
	TMatrix(const TMatrix& A);                    
	TMatrix(const TVector<TVector<ValType> >& A); 
	bool operator==(const TMatrix& A) const;      
	bool operator!=(const TMatrix& A) const;      
	TMatrix& operator= (const TMatrix& A);        
	TMatrix  operator+ (const TMatrix& A);        
	TMatrix  operator- (const TMatrix& A);        


	friend istream& operator>>(istream& in, TMatrix& A)
	{
		for (int i = 0; i < A.Size; i++)
			in >> A.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& A)
	{
		for (int i = 0; i < A.Size; i++)
			out << A.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s < 0) || (s > MAX_MATRIX_SIZE))
		throw ("negative or too large size");
	for (int i = FirstIndex; i < s; i++)
		pVector[i] = TVector<ValType>(s, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& A) :
	TVector<TVector<ValType> >(A) {}

template <class ValType> 
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& A) :
	TVector<TVector<ValType> >(A) {}

template <class ValType> 
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& A) const
{
	if (Size != A.Size)
		return false;
	if (FirstIndex != A.FirstIndex)
		return false;
	for (int i = FirstIndex; i < Size; i++)
		if (pVector[i] != A.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& A) const
{
	return !(*this == A);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& A)
{
	if (this != &A)
	{
		delete[]pVector;
		Size = A.Size;
		FirstIndex = A.FirstIndex;
		pVector = new TVector<ValType>[Size];
		for (int i = FirstIndex; i < Size; i++)
			pVector[i] = A.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& A)
{
	if (Size != A.Size)
		throw ("Sizes dont equal");
	if (FirstIndex != A.FirstIndex)
		throw ("Start indexes dont equal");
	TMatrix<ValType> res(Size);
	for (int i = FirstIndex; i < Size; i++)
		res[i] = pVector[i] + A.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	if (Size != mt.Size)
		throw ("Sizes dont equal");
	if (FirstIndex != mt.FirstIndex)
		throw ("Start indexes dont equal");
	TMatrix<ValType> res(Size);
	for (int i = FirstIndex; i < Size; i++)
		res[i] = pVector[i] - mt.pVector[i];
	return res;
}

