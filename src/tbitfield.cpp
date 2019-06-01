// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len <= 0) throw 0;
  bitLen = len;
  memLen = floor(bitLen / sizeof(TELEM));
  memLen++;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  if (pMem)
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return (n / sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n / sizeof(TELEM)) == (memLen - 1))
    return  1 << ((bitLen % sizeof(TELEM)) - (n % sizeof(TELEM)));
  return 1 << (sizeof(TELEM) - (n % sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= bitLen) throw 0;
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= bitLen) throw 0;
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > bitLen) throw 0;
  return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if(bf != *this)
  {
    delete[]pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
  }
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bitLen == bf.bitLen)
  {
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
        return 0;
	return 1;
  }
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (bitLen == bf.bitLen)
  {
    for (int i = 0; i < memLen; i++)
      if (pMem[i] != bf.pMem[i])
	    return 1;
	  return 0;
  }
  return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TELEM max = 0;
  bitLen > bf.bitLen ? max = bitLen : max = bf.bitLen;
  TBitField tmp(max);
  for (int i = 0; i < memLen; i++)
    tmp.pMem[i] = tmp.pMem[i] | pMem[i];
  for (int i = 0; i < bf.memLen; i++)
    tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if (bitLen > bf.bitLen)
  {
    TBitField tmp(bitLen);
    for (int i = 0; i < bf.memLen; i++)
	  tmp.pMem[i] = pMem[i] & bf.pMem[i];
	return tmp;
  }
  else
  {
    TBitField tmp(bf.bitLen);
	for (int i = 0; i < memLen; i++)
	  tmp.pMem[i] = bf.pMem[i] & pMem[i];
	return tmp;
  }
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField tmp(*this);
  for (int i = 0; i < tmp.bitLen; i++)
    if (tmp.GetBit(i))
	  tmp.ClrBit(i);
	else
	  tmp.SetBit(i);
  return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  return ostr;
}
