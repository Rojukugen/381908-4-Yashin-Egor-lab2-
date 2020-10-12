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
} 

#endif 
