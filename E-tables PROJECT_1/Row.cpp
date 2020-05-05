#include "Row.h"

Row::Row(int id)
{
	capacity = 4;
	row = new Cell[capacity];
	this->id = id;
}

void Row::addCell(String& value, int posOfCell)
{
	if (capacity > posOfCell)
		row[posOfCell] = *new Cell(value.getStr(), id, posOfCell);

	else
	{
		Cell* helper = new Cell[posOfCell + 1];

		for (int i = 0; i < capacity; i++)
		{
			helper[i] = row[i];
		}
		delete[] row;

		row = new Cell[posOfCell + 1];
		row = helper;

		capacity = posOfCell + 1;

		row[posOfCell] = *new Cell(value.getStr(), id, posOfCell);
	}
}

void Row::print() const
{
	for (int i = 0; i < capacity; i++)
	{
		row[i].print();
		cout << " ";
	}

	cout << endl;
}