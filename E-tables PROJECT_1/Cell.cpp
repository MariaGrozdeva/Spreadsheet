#include "Cell.h"

Cell::Cell() : value()
{
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

const char* Cell::getValue() const
{
	return value.getStr();
}

void Cell::print() const
{
	value.print();
}