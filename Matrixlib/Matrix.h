#pragma once
#include "MyVector.h"

template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s < 0) || (s > MAX_MATRIX_SIZE))
		throw ("negative or too large size");
	for (int i = StartIndex; i < s; i++)
		pVector[i] = TVector<ValType>(s, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	if (Size != mt.Size)
		return false;
	if (StartIndex != mt.StartIndex)
		return false;
	for (int i = StartIndex; i < Size; i++)
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	if (this != &mt)
	{
		delete[]pVector;
		Size = mt.Size;
		StartIndex = mt.StartIndex;
		pVector = new TVector<ValType>[Size];
		for (int i = StartIndex; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	if (Size != mt.Size)
		throw ("Sizes dont equal");
	if (StartIndex != mt.StartIndex)
		throw ("Start indexes dont equal");
	TMatrix<ValType> res(Size);
	for (int i = StartIndex; i < Size; i++)
		res[i] = pVector[i] + mt.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	if (Size != mt.Size)
		throw ("Sizes dont equal");
	if (StartIndex != mt.StartIndex)
		throw ("Start indexes dont equal");
	TMatrix<ValType> res(Size);
	for (int i = StartIndex; i < Size; i++)
		res[i] = pVector[i] - mt.pVector[i];
	return res;
}