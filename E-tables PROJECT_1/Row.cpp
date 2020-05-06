#include "Row.h"

Row::Row(int id)
{
	capacity = 4;
	cells = new Cell[capacity];
	this->id = id;
}

void Row::addCell(String& value, int posOfCell)
{
	if (capacity > posOfCell)
		cells[posOfCell] = *new Cell(value.getStr(), id, posOfCell);

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
	}
}
void Row::changeCell(String& value, int posOfCell)
{
	if (capacity > posOfCell)
		cells[posOfCell] = *new Cell(value.getStr(), id, posOfCell);
	else
		cout << "Nothing to edit, this cell doesn't exist." << endl;
}

void Row::print() const
{
	for (int i = 1; i < capacity; i++)
	{
		cells[i].print();
		cout << " ";
	}

	cout << endl;
}