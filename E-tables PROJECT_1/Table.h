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

	void setLhsValue(const char*& cell, int& start, int& finish, int& lhsRow, int& lhsCol, int& digit, char& Operator);
	void setRhsValue(const char*& cell, int& finish, int& start, int& rhsRow, int& rhsCol, int& digit, int& len);

	void checkIfRhsValueIsFormula(const char*& cell, int& lastDigPosBefOp, int& len, bool& isRhsFormula);

	bool setLhsValueAsNum(const char*& cell, double& lhsCell, int& digit, char& Operator);
	bool setRhsValueAsNum(const char*& cell, int& start, double& rhsCell, int& digit, int& len, bool& isRhsNum);

	void settingFinalCellValue(int& row, int& col, double& cell, bool& rowOrColExist);

	double arithmeticOperations(char& Operator, double& lhsCell, double& rhsCell);

	bool calculateStandartFormula(int row, int col, double& lhsNum, double& rhsNum, char& Operator);
	bool calculateFormulaCellsReference(int row, int col, double& res);

	void print();
};