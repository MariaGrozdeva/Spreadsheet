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
	void calculateStandartFormula(int row, int col, double& lhsNum, double& rhsNum, char& Operator) const;

	void print() const;
};