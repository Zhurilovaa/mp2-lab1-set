// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp > 0)
	{
		MaxPower = mp;
	}
	else throw mp;
}

TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)// Конструктор копирования
{
} 

TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) // Конструктор преобразования типа
{
}
TSet::operator TBitField() // Преобразование тип множества к битовому полю
{
	TBitField Res(this->BitField);
	return Res;
}

// доступ к битам

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int res = BitField.GetBit(Elem);
	return res;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int power = MaxPower;
	if (MaxPower < s.GetMaxPower())
	{
		power = s.GetMaxPower();
	}
	TSet res(power);
	res.BitField = BitField | s.BitField;
	return res;
}


TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(BitField);
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(BitField);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(MaxPower);
	res.BitField = BitField & s.BitField;
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(MaxPower);
	res.BitField = ~BitField;
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char c;
	int len = s.BitField.GetLength();

	for (int i = 0; i < len; ++i)
	{
		istr >> c;
		if (c == '1')
		{
			s.BitField.SetBit(i);
		}
		else
			if (c == '0')
			{
				s.BitField.ClrBit(i);
			}
			else break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int len = s.BitField.GetLength();
	for (int i = 0; i < len; ++i)
	{
		ostr << s.BitField.GetBit(i) << ' ';
		if ((i % 20) == 0 && (i != 0))
		{
			ostr << endl;
		}
	}
	ostr << endl;
	return ostr;
}