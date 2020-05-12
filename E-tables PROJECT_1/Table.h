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

	void setLhsValue(const char*& cellStr, int& lastDigPosBefCol,
		int& lastDigPosBefOp, int& lhsRow, int& lhsCol, int& digit, char& Operator);

	void setRhsValue(const char*& cellStr, int& lastDigPosBefCol,
		int& lastDigPosBefOp, int& lhsRow, int& lhsCol, int& digit, int& len);

	void checkIfRhsValueIsFormula(const char*& cellStr, int& lastDigPosBefOp, int& len, bool& isRhsFormula);

	void setLhsValueAsNum(const char*& cellStr, double& lhsCell,
		int& digit, char& Operator);

	void setRhsValueAsNum(const char*& cellStr, int& lastDigPosBefOp,
		double& rhsCell, int& digit, int& len, bool& isRhsNum);

	double arithmeticOperations(char& Operator, double& lhsCell, double& rhsCell);

	double calculateFormulaCellsReference(int row, int col);

	void calculateStandartFormula(int row, int col, double& lhsNum, double& rhsNum, char& Operator);

	void print();
};