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

// -1(invalid), 0(string), 1(number)
int Cell::checkValueType(const String& value)
{
	int len = strlen(value.getStr());

	if ((value.getStr()[0] == '"') && (value.getStr()[len - 1] == '"'))
	{
		//cout << "The value type is valid. It is string." << endl;
		return 0;
	}

	if ((value.getStr()[0] == '+') || (value.getStr()[0] == '-'))
	{
		for (int i = 1; i < len; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
			{
				//cout << "The value type is invalid." << endl;
				return -1;
			}
		}
	}
	else if ((value.getStr()[0] != '+') && (value.getStr()[0] != '-'))
	{
		for (int i = 0; i < len; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
			{
				//cout << "The value type is invalid." << endl;
				return -1;
			}
		}
	}

	int countOfDots = 0;
	for (int i = 0; i < len; i++)
	{
		if (value.getStr()[i] == '.')
			countOfDots++;
	}

	if ((countOfDots > 1) || (value.getStr()[0] == '.') || (value.getStr()[len - 1] == '.'))
	{
		//cout << "The value type is invalid. The dots can't be more than one." << endl;
		return -1;
	}

	//cout << "The value type is valid." << endl;
	return 1;
}

bool Cell::checkIfStringIsValidNumber(const String& value)
{
	int len = strlen(value.getStr());

	if (checkValueType(value) || (checkValueType(value) == -1))
	{
		cout << "The value type is not string" << endl;
		return false;
	}

	if ((value.getStr()[1] == '+') || (value.getStr()[1] == '-'))
	{
		for (int i = 2; i < len - 1; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
			{
				cout << "The value type is invalid." << endl;
				return false;
			}
		}
	}
	else if ((value.getStr()[1] != '+') && (value.getStr()[1] != '-'))
	{
		for (int i = 1; i < len - 1; i++)
		{
			if ((value.getStr()[i] != '.') && ((value.getStr()[i] < '0') || (value.getStr()[i] > '9')))
			{
				cout << "The value type is invalid." << endl;
				return false;
			}
		}
	}

	int countOfDots = 0;
	for (int i = 0; i < len; i++)
	{
		if (value.getStr()[i] == '.')
			countOfDots++;
	}

	if ((countOfDots > 1) || (value.getStr()[0] == '.') || (value.getStr()[len - 1] == '.'))
	{
		cout << "Invalid number. The dots can't be more than one." << endl;
		return false;
	}

	cout << "Valid number." << endl;
	return true;
}

void Cell::print() const
{
	value.print();
}