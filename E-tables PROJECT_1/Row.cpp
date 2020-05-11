#include "Row.h"

Row::Row(int id)
{
	capacity = 4;
	cells = new Cell[capacity];
	this->id = id;
}

Cell* Row::getCells() const
{
	return cells;
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
	if (cells[index].checkValueType(cells[index].getValue()) == 2)
	{
		return true;
	}
	return false;
}

void Row::addOrEditCell(const String& value, int posOfCell)
{
	if (capacity > posOfCell)
	{
		cells[posOfCell] = *new Cell(value.getStr(), id, posOfCell);
		if (cells[posOfCell].checkValueType(value) == -1)
		{
			cout << "Error: row:" << id << ", col:" << posOfCell << ", ";
			cells[posOfCell].getValue().print();
			cout << " is unknown data type." << endl;

			return;
		}
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
		if (cells[posOfCell].checkValueType(value) == -1)
		{
			cout << "Error: row:" << id << ", col:" << posOfCell << ", ";
			cells[posOfCell].getValue().print();
			cout << " is unknown data type." << endl;

			return;
		}
	}
}

void Row::printCell(int index) const
{
	cells[index].print();
	cout << " ";
}
void Row::print() const
{
	for (int i = 1; i < capacity; i++)
	{
		printCell(i);
	}
	cout << endl;
}