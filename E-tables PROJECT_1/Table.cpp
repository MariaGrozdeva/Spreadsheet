#include "Table.h"

double Table::calculateFormulaCellsReference(int row, int col) const // assume that the given formula is valid
{
	int digit = 0;
	int lhsRow = 0;
	int lhsCol = 0;
	int rhsRow = 0;
	int rhsCol = 0;

	int len = strlen(rows[row].getCellStr(col));
	const char* cell = rows[row].getCellStr(col);

	int lastDigPosBefCol = 3;
	int lastDigPosBefOp = 5;

	for (int i = lastDigPosBefCol; cell[i] >= '0' && cell[i] <= '9'; i++)
	{
		digit = cell[i] - '0';
		lhsRow = lhsRow * 10 + digit;

		lastDigPosBefCol = i;
	}
	digit = 0;
	for (int i = lastDigPosBefCol + 2; cell[i] >= '0' && cell[i] <= '9'; i++)
	{
		digit = cell[i] - '0';
		lhsCol = lhsCol * 10 + digit;

		lastDigPosBefOp = i;
	}

	digit = 0;
	lastDigPosBefCol = lastDigPosBefOp + 5;

	char Operator = cell[lastDigPosBefOp + 2];

	for (int i = lastDigPosBefOp + 5; cell[i] >= '0' && cell[i] <= '9'; i++)
	{
		digit = cell[i] - '0';
		rhsRow = rhsRow * 10 + digit;

		lastDigPosBefCol = i;
	}
	digit = 0;
	for (int i = lastDigPosBefCol + 2; i < len; i++)
	{
		digit = cell[i] - '0';
		rhsCol = rhsCol * 10 + digit;
	}

	double lhsCell = rows[lhsRow].getCellValue(lhsCol);
	double rhsCell = rows[rhsRow].getCellValue(rhsCol);

	if (!rows[lhsRow].getCells()->checkIfStringIsValidNumber(rows[lhsRow].getCells()[lhsCol].getValue()))
		lhsCell = 0;

	if (!rows[rhsRow].getCells()->checkIfStringIsValidNumber(rows[rhsRow].getCells()[rhsCol].getValue()))
		rhsCell = 0;

	if (Operator == '+')
		return lhsCell + rhsCell;
	else if (Operator == '-')
		return lhsCell - rhsCell;
	else if (Operator == '*')
		return lhsCell * rhsCell;
	else if (Operator == '/')
		return lhsCell / rhsCell;
	else if (Operator == '^')
		return pow(lhsCell, rhsCell);
}

Table::Table()
{
	maxRow = 1;

	rows = new Row(maxRow);
}

void Table::addRow(int numOfRow)
{
	if (maxRow <= numOfRow)
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

void Table::edit(const String& value, int row, int col)
{
	if (maxRow <= row)
	{
		addRow(row);
		rows[row].addOrEditCell(value, col);

		maxRow = row + 1;
	}
	else
		rows[row].addOrEditCell(value, col);
}

void Table::print() const
{
	for (int i = 1; i < maxRow; i++)
	{
		for (int j = 1; j < rows[i].getCapacity(); j++)
		{
			if (rows[i].isFormula(j))
			{
				cout << calculateFormulaCellsReference(i, j) << " ";
			}
			else
				rows[i].printCell(j);
		}

		cout << endl;
	}
}