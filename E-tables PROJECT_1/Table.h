#include "Row.h"

class Table
{
private:
	Row* rows;
	int maxRow;
	int maxCol;

public:
	Table();

	void addRow(int numOfRow);

	void addCellinTable(String& value, int row, int col);

	void print() const;
};