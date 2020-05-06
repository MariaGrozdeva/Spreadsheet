#include "Table.h"

Table::Table()
{
	maxRow = 1;

	rows = new Row(maxRow);
}

void Table::addRow(int numOfRow)
{
	if (maxRow > numOfRow)
		cout << "This row already exists" << endl;

	else
	{
		Row* helper = new Row[numOfRow + 1]; // Редът с индекс 5, ще е 6ти.

		for (int i = 0; i < maxRow; i++)
		{
			helper[i] = rows[i];
		}
		delete[] rows;

		rows = new Row[numOfRow + 1];
		rows = helper;

		maxRow = numOfRow + 1;

		rows[numOfRow] = *new Row(numOfRow);
	}
}

void Table::addCellinTable(String& value, int row, int col)
{
	if (maxRow <= row)
	{
		addRow(row);
		rows[row].addCell(value, col);

		maxRow = row + 1;
	}
	else
		rows[row].addCell(value, col);
}

void Table::edit(String& value, int row, int col)
{
	if (maxRow <= row)
	{
		cout << "Nothing to edit, this row doesn't exist." << endl;
	}
	else
		rows[row].changeCell(value, col);
}

void Table::print() const
{
	for (int i = 1; i < maxRow; i++)
	{
		rows[i].print();
	}
}