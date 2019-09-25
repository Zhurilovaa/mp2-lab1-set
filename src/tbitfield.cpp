// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) // конструктор
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i)
		{
			pMem[i] = 0;
		}
	}
	else throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() // деструктор
{
	delete[] pMem;
	pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс элемента в Мем, содержащего бит n
{
	int res = (n / (sizeof(TELEM) * 8));
	return res;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int tmp = n % (sizeof(TELEM) * 8); // положение бита в элементе
	TELEM mask = 1 << tmp;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((-1 < n) && (n < BitLen))
	{
		int i = GetMemIndex(n); // индекс эл-та в Mem содержащий бит n
		TELEM mask = GetMemMask(n); // маска
		pMem[i] = pMem[i] | mask;
	}
	else throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((-1 < n) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		pMem[i] = pMem[i] & (~mask);
	}
	else throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((-1 < n) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		return ((pMem[i] & GetMemMask(n)) == 0 ? 0 : 1);
	}
	else throw n;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) //Контроль самоприсвоивания
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		if (bf.pMem != NULL)
		{
			delete[] pMem;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; ++i)
			{
				pMem[i] = bf.pMem[i];
			}
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	if (MemLen != bf.MemLen)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}
			else return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 1;
	}
	if (MemLen != bf.MemLen)
	{
		return 1;
	}
	else
	{
		int prov = 0;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
			{
				prov++;
			}
		if (prov == MemLen)
		{
			return 0;
		}
		else
			return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int Len = BitLen;
	if (BitLen < bf.BitLen)
		Len = bf.BitLen;
	TBitField res(Len);
	for (int i = 0; i < MemLen; ++i)
	{
		res.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; ++i)
	{
		res.pMem[i] |= bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(bf.BitLen > BitLen ? bf.BitLen : BitLen);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] &= bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < BitLen; i++)
	{
		pMem[GetMemIndex(i)] ^= GetMemMask(i);
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c;
	int len = bf.GetLength();

	for (int i = 0; i < len; ++i)
	{
		istr >> c;
		if (c == '1')
		{
			bf.SetBit(i);
		}
		else
			if (c == '0')
			{
				bf.ClrBit(i);
			}
			else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = len-1; i >=0; --i)
	{
		ostr << bf.GetBit(i) << ' ';
	}
	ostr << endl;
	return ostr;
}
