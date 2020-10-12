
#ifndef _MATRIX_
#define _MATRIX_
#include "MyVector.h"

const int MAX_MATRIX_SIZE = 100000;


template <class ValType> //Âåðõíåòðåóãîëüíàÿ ìàòðèöà
class TMatrix : public TVector<TVector<ValType> >
{
private:
  int mSize;
public:
  TMatrix(int s);
  TMatrix(const TMatrix& mt);                        //êîïèðîâàíèå
  TMatrix(const TVector<TVector<ValType> >& mt);    //ïðåîáðàçîâàíèå òèïà
  ~TMatrix();

  int GetSize() { return mSize; };               //Ïîëó÷åíèå ðàçìåðà Ìàòðèöû
  bool operator==(const TMatrix& mt) const;     //ñðàâíåíèå Ìàòðèö
  TMatrix operator= (const TMatrix& mt);       //ïðèñâàèâàíèå Ìàòðèö
  TMatrix  operator+ (const TMatrix& mt);     //ñëîæåíèå Ìàòðèö
  TMatrix  operator- (const TMatrix& mt);    //âû÷èòàíèå Ìàòðèö
  TMatrix  operator* (const TMatrix& mt);   //óìíîæåíèå Ìàòðèö

  // ââîä / âûâîä
  friend istream& operator>>(istream& in, TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
    {
      in >> mt.pVector[i];
    }
    return in;
  }
  friend ostream& operator<<(ostream& out, const TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
    {
      out << mt.pVector[i] << endl;
    }
    return out;
  }
};

template<class ValType>
inline TMatrix<ValType>::TMatrix(int s) : TVector<TVector <ValType> >(s)
{
  if (s < 0 || s > MAX_MATRIX_SIZE)
  {
    throw  logic_error("ERROR");
  }
  mSize = s;
}

template <class ValType> //êîíñòðóêòîð êîïèðîâàíèÿ
inline TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType> >(mt)
{
  mSize = mt.Size;
}

template <class ValType> //êîíñòðóêòîð ïðåîáðàçîâàíèÿ òèïà
inline TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) : TVector<TVector<ValType> >(mt)
{

}

template<class ValType>
inline TMatrix<ValType>::~TMatrix()
{
  if (mSize != 0)
  {
    mSize = NULL;
  }
}

template <class ValType> //ñðàâíåíèå
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  bool res = true;
  int S = this->Size;

  if (S != mt.Size)
  {
    res = false;
  }

  for (int i = 0; i < S; i++)
  {
    if (this->pVector[i] == mt.pVector[i])
    {
      res = true;
    }
    else res = false;
  }

  return res;
}

template <class ValType> //ïðèñâàèâàíèå
inline TMatrix<ValType> TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this != &mt)
  {
    if (this->Size != mt.Size)
    {
      if (this->pVector != NULL)
      {
        delete[] this->pVector;
      }
      this->pVector = new TVector<ValType>[mt.Size];
    }

    this->Size = mt.Size;

    for (int i = 0; i < this->Size; i++)
    {
      this->pVector[i] = mt.pVector[i];
    }
  }

  return *this;
}

template <class ValType> // ñëîæåíèå
inline TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  if (this->GetSize() != mt.Size)
  {
    throw  logic_error("ERROR");
  }

  TMatrix<ValType> temp(*this);

  for (int i = 0; i < this->Size; i++)
  {
    temp.pVector[i] = temp.pVector[i] + mt.pVector[i];
  }
  return temp;
}

template <class ValType> //âû÷èòàíèå
inline TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  if (this->GetSize() != mt.Size)
  {
    throw  logic_error("ERROR");
  }

  TMatrix<ValType> temp(*this);

  for (int i = 0; i < this->Size; i++)
  {
    temp.pVector[i] = temp.pVector[i] - mt.pVector[i];
  }
  return temp;
}

template<class ValType>
inline TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& mt)
{
  TMatrix<ValType> temp(*this);

  for (int i = 0; i < this->Size; i++)
  {
    temp.pVector[i] = temp.pVector[i] * mt.pVector[i];
  }
  return temp;
}

#endif