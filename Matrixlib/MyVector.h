
#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000;

//Øàáëîí âåêòîðà
template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size;
public:
  TVector();
  TVector(int _v);
  TVector(int s, int si);
  TVector(const TVector& v);                // êîíñòðóêòîð êîïèðîâàíèÿ
  virtual ~TVector();

  int GetSize() { return Size; }            // ðàçìåð âåêòîðà

  ValType& operator[](int pos);              // äîñòóï
  bool operator==(const TVector& v) const;  // ñðàâíåíèå
  TVector& operator=(const TVector& v);    // ïðèñâàèâàíèå

  // ñêàëÿðíûå îïåðàöèè
  TVector  operator+(const ValType& val);    // ïðèáàâèòü 
  TVector  operator-(const ValType& val);   // âû÷åñòü 
  TVector  operator*(const ValType& val);  // óìíîæèòü 
  TVector  operator/(const ValType& val); //äåëèòü 

  // âåêòîðíûå îïåðàöèè
  TVector  operator+(const TVector& v);     // ñëîæåíèå
  TVector  operator-(const TVector& v);    // âû÷èòàíèå
  TVector  operator*(const TVector& v);   // ñêàëÿðíîå ïðîèçâåäåíèå

   // ââîä-âûâîä
  friend istream& operator>>(istream& in, TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
    {
      in >> v.pVector[i];
    }
    return in;
  }

  friend ostream& operator<<(ostream& out, const TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
    {
      out << v.pVector[i] << '\t';
    }
    return out;
  }
};

template<class ValType>
inline TVector<ValType> ::TVector()
{
  Size = NULL;
}

template<class ValType>
TVector<ValType>::TVector(int v)
{
  if (v < 0 || v > MAX_VECTOR_SIZE)
  {
    throw  logic_error("ERROR");
  }

  Size = v;
  pVector = new ValType[Size];

  for (int i = 0; i < Size; i++)
  {
    pVector[i] = v;
  }

}

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
  if (si < 0)
  {
    throw  logic_error("ERROR");
  }

  Size = s;
  pVector = new ValType[Size];

  for (int i = 0; i < Size; i++)
  {
    pVector[i] = si;
  }
}

template <class ValType> //êîíñòðóêòîð êîïèðîâàíèÿ
TVector<ValType>::TVector(const TVector<ValType>& v)
{
  Size = v.Size;
  pVector = new ValType[Size];

  for (int i = 0; i < Size; i++)
  {
    pVector[i] = v.pVector[i];
  }
}

template <class ValType>
TVector<ValType>::~TVector()
{
  Size = NULL;

  if (pVector != 0)
  {
    delete[] pVector;
  }

  pVector = NULL;
}

template <class ValType> // äîñòóï
ValType& TVector<ValType>::operator[](int index)
{
  if (index < 0 || index > Size)
  {
    throw  logic_error("ERROR");
  }

  if ((index >= 0) && (index < Size))
  {
    return pVector[index];
  }

  return pVector[0];
}

template <class ValType> // ñðàâíåíèå
bool TVector<ValType>::operator==(const TVector& v) const
{
  bool res = true;
  if (Size != v.Size)
  {
    res = false;
  }

  for (int i = 0; i < Size; i++)
  {
    if (pVector[i] != v.pVector[i])
    {
      res = false;
    }
  }
  return res;
}

template <class ValType> //ïðèñâàèâàíèå
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
  if (this == &v)
  {
    return *this;
  }

  Size = v.Size;
  pVector = new ValType[Size];

  for (int i = 0; i < Size; i++)
  {
    pVector[i] = v.pVector[i];
  }
  return *this;
}

template <class ValType> //ïðèáàâèòü 
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] + val;
  }
  return res;
}

template <class ValType> //âû÷åñòü 
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] - val;
  }
  return res;
}

template <class ValType> //óìíîæèòü 
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] * val;
  }
  return res;
}

template<class ValType>
inline TVector<ValType> TVector<ValType>::operator/(const ValType& val)
{
  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] / val;
  }
  return res;
}

template <class ValType> //ñëîæåíèå
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
  if (v.Size != Size)
  {
    throw  logic_error("ERROR");
  }

  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] + v.pVector[i];
  }
  return res;
}

template <class ValType> //âû÷èòàíèå
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
  if (v.Size != Size)
  {
    throw  logic_error("ERROR");
  }

  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] - v.pVector[i];
  }
  return res;
}

template <class ValType> //ñêàëÿðíîå ïðîèçâåäåíèå
TVector<ValType> TVector<ValType> ::operator*(const TVector<ValType>& v)
{
  if (v.Size != Size)
  {
    throw  logic_error("ERROR");
  }

  TVector<ValType> res;
  res.Size = Size;
  res.pVector = new ValType[res.Size];

  for (int i = 0; i < res.Size; i++)
  {
    res.pVector[i] = pVector[i] * v.pVector[i];
  }
  return res;
}
#endif