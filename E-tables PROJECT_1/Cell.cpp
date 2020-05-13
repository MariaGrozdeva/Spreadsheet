#include "Cell.h"

Cell::Cell()
{
	value.setStr(",,");
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


// -1(invalid), 0(string), 1(number), 2(formula)
int Cell::checkValueType(const String& value)
{
	int len = strlen(value.getStr());

	if ((value.getStr()[0] == '"') && (value.getStr()[len - 1] == '"'))
		return 0;

	if (value.getStr()[0] == '=')
		return 2;

	if ((value.getStr()[0] == '+') || (value.getStr()[0] == '-'))
	{
		for (int i = 1; i < len; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
				return -1;
		}
	}
	else if ((value.getStr()[0] != '+') && (value.getStr()[0] != '-'))
	{
		for (int i = 0; i < len; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
				return -1;
		}
	}

	int countOfDots = 0;
	for (int i = 0; i < len; i++)
	{
		if (value.getStr()[i] == '.')
			countOfDots++;
	}

	if ((countOfDots > 1) || (value.getStr()[0] == '.') || (value.getStr()[len - 1] == '.'))
		return -1;

	return 1;
}

bool Cell::checkIfStringIsValidNumber(const String& value)
{
	int len = strlen(value.getStr());

	if (checkValueType(value) || (checkValueType(value) == -1))
		return false;

	if ((value.getStr()[1] == '+') || (value.getStr()[1] == '-'))
	{
		for (int i = 2; i < len - 1; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
				return false;
		}
	}
	else if ((value.getStr()[1] != '+') && (value.getStr()[1] != '-'))
	{
		for (int i = 1; i < len - 1; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
				return false;
		}
	}

	int countOfDots = 0;
	for (int i = 0; i < len; i++)
	{
		if (value.getStr()[i] == '.')
			countOfDots++;
	}

	if ((countOfDots > 1) || (value.getStr()[0] == '.') || (value.getStr()[len - 1] == '.'))
		return false;

	return true;
}

double Cell::convertStrToNum()
{
	double number = 0;
	double digit = 0;

	if (!checkIfStringIsValidNumber(value))
		return 0;

	int len = strlen(value.getStr());
	int isFract = 0;

	for (int i = 1; i < len - 1; i++)
	{
		if (value.getStr()[i] == '.')
		{
			isFract = i;
			break;
		}
	}

	bool hasSign = false;
	bool isPlus = true;
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

	if (!isFract)
	{
		for (int i = 1 + hasSign; i < len - 1; i++)
		{
			digit = value.getStr()[i] - '0';
			number = number * 10 + digit;
		}
	}
	else
	{
		for (int i = 1 + hasSign; i < isFract; i++)
		{
			digit = value.getStr()[i] - '0';
			number = number * 10 + digit;
		}
		for (int i = isFract + 1, j = 1; i < len - 1; i++, j++)
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