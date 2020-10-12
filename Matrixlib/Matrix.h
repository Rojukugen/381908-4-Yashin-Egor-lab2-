#pragma once
#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);                // ����������� �����������
	~TVector();
	int GetSize() { return Size; } // ������ �������
	int GetStartIndex() { return StartIndex; } // ������ ������� ��������
	ValType& operator[](int pos);             // ������
	bool operator==(const TVector& v) const;  // ���������
	bool operator!=(const TVector& v) const;  // ���������
	TVector& operator=(const TVector& v);     // ������������

	// ��������� ��������
	TVector  operator+(const ValType& val);   // ��������� ������
	TVector  operator-(const ValType& val);   // ������� ������
	TVector  operator*(const ValType& val);   // �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector& v);     // ��������
	TVector  operator-(const TVector& v);     // ���������
	ValType  operator*(const TVector& v);     // ��������� ������������

	// ����-�����
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s < 0)
		throw ("Negative size");
	if (s > MAX_VECTOR_SIZE)
		throw ("Size more than MAX_VECTOR_SIZE");
	if ((si < 0) || (si > s))
		throw ("Out of range");
	Size = s;
	StartIndex = si;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType>& v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != NULL)
		delete[]pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < StartIndex) || (pos >= (Size + StartIndex)))
		throw ("Incorrect index");
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (this != &v)
	{
		if (Size != v.Size)
			return false;
		else if (StartIndex != v.StartIndex)
			return false;
		else
			for (int i = 0; i < Size; i++)
				if (pVector[i] != v.pVector[i])
				{
					return false;
					break;
				}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this != &v)
	{
		delete[]pVector;
		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[Size];
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> v = *this;
	for (int i = 0; i < Size; i++)
		v.pVector[i] = v.pVector[i] + val;
	return v;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector v = *this;
	for (int i = 0; i < Size; i++)
		v.pVector[i] = v.pVector[i] - val;
	return v;
} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector v = *this;
	for (int i = 0; i < Size; i++)
		v.pVector[i] *= val;
	return v;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw ("Sizes dont equal");
	if (StartIndex != v.StartIndex)
		throw ("Start indexes dont equal");
	TVector res(Size);
	for (int i = 0; i < Size; i++)
		res[i] = pVector[i] + v.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw ("Sizes dont equal");
	if (StartIndex != v.StartIndex)
		throw ("Start indexes dont equal");
	TVector res(Size);
	for (int i = 0; i < Size; i++)
		res[i] = pVector[i] - v.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw ("Sizes dont equal");
	if (StartIndex != v.StartIndex)
		throw ("Start indexes dont equal");
	ValType res = 0;
	for (int i = 0; i < Size; i++)
		res = res + pVector[i] * v.pVector[i];
	return res;
} /*-------------------------------------------------------------------------*/


// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // �����������
	TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
	bool operator==(const TMatrix& mt) const;      // ���������
	bool operator!=(const TMatrix& mt) const;      // ���������
	TMatrix& operator= (const TMatrix& mt);        // ������������
	TMatrix  operator+ (const TMatrix& mt);        // ��������
	TMatrix  operator- (const TMatrix& mt);        // ���������

	// ���� / �����
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

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
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

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
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

template <class ValType> // ��������
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

template <class ValType> // ���������
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
} /*-------------------------------------------------------------------------*/

// TVector �3 �2 �4 �6
// TMatrix �2 �2 �3 �3
#endif