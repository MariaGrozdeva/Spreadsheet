#include "Table.h"

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
		maxCol = rows[row].getCapacity();
	}
	else
		rows[row].addOrEditCell(value, col);
}

void Table::setLhsValue(const char*& cellStr, int& lastDigPosBefCol,
	int& lastDigPosBefOp, int& lhsRow, int& lhsCol, int& digit, char& Operator)
{
	for (int i = lastDigPosBefCol; cellStr[i] >= '0' && cellStr[i] <= '9'; i++)
	{
		digit = cellStr[i] - '0';
		lhsRow = lhsRow * 10 + digit;

		lastDigPosBefCol = i;
	}
	digit = 0;
	for (int i = lastDigPosBefCol + 2; cellStr[i] >= '0' && cellStr[i] <= '9'; i++)
	{
		digit = cellStr[i] - '0';
		lhsCol = lhsCol * 10 + digit;

		lastDigPosBefOp = i;
	}
	digit = 0;
	lastDigPosBefCol = lastDigPosBefOp + 5;

	Operator = cellStr[lastDigPosBefOp + 2];
}

void Table::setRhsValue(const char*& cellStr, int& lastDigPosBefCol,
	int& lastDigPosBefOp, int& rhsRow, int& rhsCol, int& digit, int& len)
{
	for (int i = lastDigPosBefOp + 5; cellStr[i] >= '0' && cellStr[i] <= '9'; i++)
	{
		digit = cellStr[i] - '0';
		rhsRow = rhsRow * 10 + digit;

		lastDigPosBefCol = i;
	}
	digit = 0;
	for (int i = lastDigPosBefCol + 2; i < len; i++)
	{
		digit = cellStr[i] - '0';
		rhsCol = rhsCol * 10 + digit;
	}
}

void Table::checkIfRhsValueIsFormula(const char*& cellStr, int& lastDigPosBefOp, int& len, bool& isRhsFormula)
{
	for (int i = 0; i < len; i++)
	{
		if (cellStr[i] == 'R')
		{
			isRhsFormula = true;
			lastDigPosBefOp = i - 4;
			break;
		}
	}
}

void Table::setLhsValueAsNum(const char*& cellStr, double& lhsCell,
	int& digit, char& Operator)
{
	int posOfDot = 0;
	bool dot = false;
	for (int i = 2; (cellStr[i] >= '0' && cellStr[i] <= '9') || (cellStr[i] == '.'); i++)
	{
		if (cellStr[i] == '.')
		{
			dot = true;
			posOfDot = i;
			break;
		}
		digit = cellStr[i] - '0';
		lhsCell = lhsCell * 10 + digit;

		Operator = cellStr[i + 2];
	}
	if (dot)
	{
		for (int i = posOfDot + 1, j = 1; cellStr[i] != ' '; i++, j++)
		{
			digit = cellStr[i] - '0';
			lhsCell = lhsCell + (digit / (pow(10, j)));

			Operator = cellStr[i + 2];
		}
	}
}

void Table::setRhsValueAsNum(const char*& cellStr, int& lastDigPosBefOp,
	double& rhsCell, int& digit, int& len, bool& isRhsNum)
{
	isRhsNum = true;

	int posOfDot = 0;
	bool dot = false;
	for (int i = lastDigPosBefOp + 4; (cellStr[i] >= '0' && cellStr[i] <= '9') || (cellStr[i] == '.'); i++)
	{
		if (cellStr[i] == '.')
		{
			dot = true;
			posOfDot = i;
			break;
		}
		digit = cellStr[i] - '0';
		rhsCell = rhsCell * 10 + digit;
	}
	if (dot)
	{
		for (int i = posOfDot + 1, j = 1; i < len; i++, j++)
		{
			digit = cellStr[i] - '0';
			rhsCell = rhsCell + (digit / (pow(10, j)));
		}
	}
}

void Table::settingFinalValue(int& row, int& col, double& cell, bool& rowOrColExist)
{
	if (row > maxRow - 1 || col > maxCol - 1)
	{
		rowOrColExist = false;
		cell = 0;
	}
	else
		cell = rows[row].getCellValue(col); // set SECOND AS FORMULA
}

double Table::arithmeticOperations(char& Operator, double& lhsCell, double& rhsCell)
{
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

double Table::calculateFormulaCellsReference(int row, int col) // assume that the given formula is valid
{
	int len = strlen(rows[row].getCellStr(col));
	const char* cell = rows[row].getCellStr(col);

	int digit = 0;
	int lhsRow = 0;
	int lhsCol = 0;
	int rhsRow = 0;
	int rhsCol = 0;

	int lastDigPosBefCol = 0;
	int lastDigPosBefOp = 0;

	double lhsCell = 0;
	double rhsCell = 0;

	bool isRhsNum = false;
	bool isRhsFormula = false;
	bool rowOrColExist = true;

	char Operator;

	if (cell[2] >= '0' && cell[2] <= '9') // check if FIRST IS NUMBER
	{
		checkIfRhsValueIsFormula(cell, lastDigPosBefOp, len, isRhsFormula); // check if SECOND IS FORMULA
		if (isRhsFormula) 
		{
			setRhsValue(cell, lastDigPosBefCol, lastDigPosBefOp, rhsRow, rhsCol, digit, len);
			settingFinalValue(rhsRow, rhsCol, rhsCell, rowOrColExist); // set SECOND AS FORMULA
		}
		setLhsValueAsNum(cell, lhsCell, digit, Operator); // set FIRST AS NUMBER
	}

	else if ((cell[2] >= '0' && cell[2] <= '9') && (!isRhsFormula)) // check if BOTH ARE NUMBERS
		calculateStandartFormula(row, col, lhsCell, rhsCell, Operator); // set BOTH AS NUMBERS

	else // FIRST IS FORMULA
	{
		lastDigPosBefCol += 3;
		lastDigPosBefOp += 5;

		setLhsValue(cell, lastDigPosBefCol, lastDigPosBefOp, lhsRow, lhsCol, digit, Operator);
		settingFinalValue(lhsRow, lhsCol, lhsCell, rowOrColExist); // set FIRST AS FORMULA

		if (cell[lastDigPosBefOp + 4] >= '0' && cell[lastDigPosBefOp + 4] <= '9') // check if SECOND IS NUMBER
			setRhsValueAsNum(cell, lastDigPosBefOp, rhsCell, digit, len, isRhsNum); // set SECOND AS NUMBER

		if (!isRhsNum) // SECOND IS FORMULA
		{
			setRhsValue(cell, lastDigPosBefCol, lastDigPosBefOp, rhsRow, rhsCol, digit, len);
			settingFinalValue(rhsRow, rhsCol, rhsCell, rowOrColExist); // set SECOND AS FORMULA

			if (rowOrColExist)
			{
				if (!rows[rhsRow].getCells()->checkIfStringIsValidNumber(rows[rhsRow].getCells()[rhsCol].getValue()))
					rhsCell = 0;
			}
		}

		if (rowOrColExist)
		{
			if (!rows[lhsRow].getCells()->checkIfStringIsValidNumber(rows[lhsRow].getCells()[lhsCol].getValue()))
				lhsCell = 0;
		}
	}

	return arithmeticOperations(Operator, lhsCell, rhsCell);
}

void Table::calculateStandartFormula(int row, int col, double& lhsNum, double& rhsNum, char& Operator)
// assume that the given formula is valid
{
	int digit = 0;
	lhsNum = 0;
	rhsNum = 0;

	int len = strlen(rows[row].getCellStr(col));
	const char* cell = rows[row].getCellStr(col);

	int posOfOp = 0;
	int posOfDot = 0;
	bool dot = false;

	for (int i = 2; (cell[i] >= '0' && cell[i] <= '9') || (cell[i] == '.'); i++)
	{
		if (cell[i] == '.')
		{
			dot = true;
			posOfDot = i;
			break;
		}

		digit = cell[i] - '0';
		lhsNum = lhsNum * 10 + digit;

		posOfOp = i + 2;
	}
	if (dot)
	{
		for (int i = posOfDot + 1, j = 1; cell[i] >= '0' && cell[i] <= '9'; i++, j++)
		{
			digit = cell[i] - '0';
			lhsNum = lhsNum + (digit / (pow(10, j)));

			posOfOp = i + 2;
		}
	}

	digit = 0;
	posOfDot = 0;
	dot = false;

	for (int i = posOfOp + 2; i < len || (cell[i] == '.'); i++)
	{
		if (cell[i] == '.')
		{
			dot = true;
			posOfDot = i;
			break;
		}

		digit = cell[i] - '0';
		rhsNum = rhsNum * 10 + digit; 
	}
	Operator = cell[posOfOp];
	if (dot)
	{
		for (int i = posOfDot + 1, j = 1; i < len; i++, j++)
		{
			digit = cell[i] - '0';
			rhsNum = rhsNum + (digit / (pow(10, j)));

			posOfOp = i + 2;
		}
	}
}

void Table::print()
{
	for (int i = 1; i < maxRow; i++)
	{
		for (int j = 1; j < rows[i].getCapacity(); j++)
		{
			if (rows[i].isFormula(j))
				cout << calculateFormulaCellsReference(i, j) << " ";
			else
				rows[i].printCell(j);
		}

		cout << endl;
	}
}