#include "Row.h"

Row::Row(int id)
{
	capacity = 4;
	cells = new Cell[capacity];
	this->id = id;
	isEmpty = true;
}

Cell* Row::getCells() const
{
	return cells;
}

bool Row::getIsEmpty() const
{
	return isEmpty;
}
const int Row::getCapacity() const
{
	return capacity;
}
const char* Row::getCellStr(int index) const
{
	return cells[index].getValueStr();
}
const double Row::getCellValue(int index) const
{
	return cells[index].convertStrToNum();
}
const String Row::getOriginalValue(int index) const
{
	return cells[index].getValue();
}

bool Row::isFormula(int index) const
{
	if (cells[index].checkIfStringIsValidNumber(cells[index].getValue()) == 2)
		return true;
	return false;
}

void Row::addOrEditCell(const String& value, int posOfCell)
{
	if (capacity > posOfCell)
	{
		cells[posOfCell] = *new Cell(value.getStr(), id, posOfCell);
		isEmpty = false;
		if (cells[posOfCell].checkIfStringIsValidNumber(value) == -1)
			return;
	}

	else
	{
		Cell* helper = new Cell[posOfCell + 1];

		for (int i = 0; i < capacity; i++)
		{
			helper[i] = cells[i];
		}
		delete[] cells;

		cells = new Cell[posOfCell + 1];
		cells = helper;

		capacity = posOfCell + 1;

		cells[posOfCell] = *new Cell(value.getStr(), id, posOfCell);
		isEmpty = false;
		if (cells[posOfCell].checkIfStringIsValidNumber(value) == -1)
			return;
	}
}

void Row::printCell(int index) const
{
	cells[index].print();
}
void Row::print() const
{
	for (int i = 1; i < capacity; i++)
		printCell(i);

	cout << endl;
}