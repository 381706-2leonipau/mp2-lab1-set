// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
  maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
  maxPower = bf.GetLength();
  bitField = bf;
}

TSet::operator TBitField()
{
  return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  if (Elem > maxPower) throw 0;
  if (bitField.GetBit(Elem))
    return 1;
  return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  if (Elem > maxPower) throw 0;
  bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  if (Elem > maxPower) throw 0;
  bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  if (s != *this)
  {
    maxPower = s.maxPower;
	bitField = s.bitField;
  }
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if ((maxPower != s.maxPower) && (bitField != s.bitField))
    return 0;
  return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  if ((maxPower == s.maxPower) && (bitField == s.bitField))
    return 0;
  return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  unsigned max = maxPower;
  if (maxPower < s.maxPower)
  {
    max = s.maxPower;
  }
  TSet tmp(max);
  tmp.bitField = bitField | s.bitField;
  return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem < 0 || Elem >= maxPower) throw 0;
  TSet tmp(maxPower);
  for (int i = 0; i < tmp.maxPower; i++)
    if (bitField.GetBit(i))
      tmp.bitField.SetBit(i);
    tmp.bitField.SetBit(Elem);
  return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (Elem < 0 || Elem >= maxPower) throw 0;
  TSet tmp(maxPower);
  for (int i = 0; i < tmp.maxPower; i++)
    if (bitField.GetBit(i))
	  tmp.bitField.SetBit(i);
  if (bitField.GetBit(Elem))
	tmp.bitField.ClrBit(Elem);
  return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  unsigned max = 1, min = 1;
  if (maxPower > s.maxPower)
  {
    max = maxPower;
	min = s.maxPower;
  }
  else
  {
    min = maxPower;
	max = s.maxPower;
  }
  TSet tmp(max);
  for (int i = 0; i < min; i++)
    if (bitField.GetBit(i) && s.bitField.GetBit(i))
	  tmp.bitField.SetBit(i);
  return tmp;
}

TSet TSet::operator~(void) // дополнение
{
  TSet tmp(*this);
  tmp.bitField = ~tmp.bitField;
  return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  return ostr;
}
