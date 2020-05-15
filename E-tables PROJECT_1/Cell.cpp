#include "Cell.h"

Cell::Cell()
{
	value.setStr(" ");
	int row = 0;
	int col = 0;
}
Cell::Cell(const char* str, int row, int col)
{
	this->value.setStr(str);

	this->row = row;
	this->col = col;
}

void Cell::setValue(const char* str)
{
	value.setStr(str);
}
void Cell::setPos(int row, int col)
{
	this->row = row;
	this->col = col;
}

const char* Cell::getValueStr() const
{
	return value.getStr();
}
const String Cell::getValue() const
{
	return value;
}

int Cell::helperForValidity(const char* str, int len, int i)
{
	for (i = 1; i < len - 1; i++)
	{
		if ((str[i] != '.') && ((str[i] < '0') || (str[i] > '9')))
			return -1;
	}
}
int Cell::helperForDotCount(const char* str, int len)
{
	int countOfDots = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '.')
			countOfDots++;
	}
	if ((countOfDots > 1) || (str[0] == '.') || (str[len - 1] == '.'))
		return -1;
	countOfDots = 0;
}
// -1(invalid), 0(string), 1(number), 2(formula)
int Cell::checkIfStringIsValidNumber(const String& value)
{
	int len = strlen(value.getStr());
	const char* str = value.getStr();
	int start = 1;

	if (str[0] == '=')
		return 2;

	if ((str[0] == '"') && (str[len - 1] == '"'))
	{
		if ((str[1] == '+') || (str[1] == '-'))
			helperForValidity(str, len, start + 1);

		else if ((str[1] != '+') && (str[1] != '-'))
			helperForValidity(str, len, start);

		helperForDotCount(str, len);
		return 0;
	}

	if ((str[0] >= '0') && (str[0] <= '9'))
	{
		int start = 0;

		if ((str[0] == '+') || (str[0] == '-'))
			start = 1;
		else if ((str[0] != '+') && (str[0] != '-'))
			start = 0;
		helperForValidity(str, len + 1, start);

		helperForDotCount(str, len);
	}	
	return 1;
}

double Cell::convertStrToNum()
{
	double number = 0;
	double digit = 0;
	int start = 0;
	int len = strlen(value.getStr());
	int isFract = 0;

	switch (checkIfStringIsValidNumber(value))
	{
	case -1: return 0;
	case 0: start = 1; break;
	case 1: start = 0; break;
	case 2: return 0;
	default: break;
	}

	for (int i = start; i < len - 1; i++)
	{
		if (value.getStr()[i] == '.')
		{
			isFract = i;
			break;
		}
	}
	bool hasSign = false;
	bool isPlus = true;
	if (start)
	{
		if (value.getStr()[1] == '+')
		{
			hasSign = true;
			isPlus = true;
		}
		else if (value.getStr()[1] == '-')
		{
			hasSign = true;
			isPlus = false;
		}
	}
	if (!isFract)
	{
		for (int i = start + hasSign; i < len - start; i++)
		{
			digit = value.getStr()[i] - '0';
			number = number * 10 + digit;
		}
	}
	else
	{
		for (int i = start + hasSign; i < isFract; i++)
		{
			digit = value.getStr()[i] - '0';
			number = number * 10 + digit;
		}
		for (int i = isFract + 1, j = 1; i < len - start; i++, j++)
		{
			digit = value.getStr()[i] - '0';
			number = number + (digit / (pow(10, j)));
		}
	}
	return isPlus ? number : -number;
}

void Cell::print() const
{
	value.print();
}