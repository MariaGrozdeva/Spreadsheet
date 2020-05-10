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

	void edit(const String& value, int row, int col);

	double calculateFormulaCellsReference(int row, int col) const;

	void print() const;
};