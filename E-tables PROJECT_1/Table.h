#include "Row.h"

class Table
{
private:
	Row* rows; /**< Dynamically allocated array of objects of type Row (undetermined number of rows and columns in a table). */
	/** Dynamically allocated array which elements are the max lengths of cells from each column.
	* Needed for the alligment in the print() command.
	*/
	int* lenOfMaxCols;
	int maxRow;
	int maxCol;

	/** All of the functions mentioned below are private member functions because they are only used inside
	* calculateFormulaCellsReference(). Their purpose is to check every possible case of an input formula
	* (when either both parts of the formula are numbers/ references to other cells or when both parts are different
	* from one another). All of them have almost all of their arguments passed by reference, because
	* when a value is changed inside them, it must save its new value after call of the function.
	* @see setLhsValue() @see setRhsValue() @see setLhsValueAsNum @see setRhsValueAsNum
	*/
	void setLhsValue(const char*& cell, int& start, int& finish, int& lhsRow, int& lhsCol, int& digit, char& Operator);
	void setRhsValue(const char*& cell, int& finish, int& start, int& rhsRow, int& rhsCol, int& digit, int& len);

	/**
	* This function checks if the right side of a formula is reference to another cell. 
	*/
	void checkIfRhsValueIsReference(const char*& cell, int& lastDigPosBefOp, int& len, bool& isRhsFormula);

	bool setLhsValueAsNum(const char*& cell, double& lhsCell, int& digit, char& Operator);
	bool setRhsValueAsNum(const char*& cell, int& start, double& rhsCell, int& digit, int& len, bool& isRhsNum);

	/**
	* This function calculates the part of the formula which is reference to another cell.
	*/
	void settingFinalCellValue(int& row, int& col, double& cell, bool& rowOrColExist);

	/**
	* This is the function which returns the final result of an operation.
	* The content of: @param lhsCell is the value of the first argument in the formula(validated and converted to
	* number, if needed, or converted to 0(if the value was invalid).
	* Similarly for: @param rhsCell (the second argument in the formula).
	*/
	double arithmeticOperations(char& Operator, double& lhsCell, double& rhsCell);
	/**
	* Private member function, used only in calculateFormulaCellsReference() when both arguments of a formula 
	* are numbers.
	*/
	bool calculateStandartFormula(int row, int col, double& lhsNum, double& rhsNum, char& Operator);

	int lenOfNum(int num); /**< Returns the length of a number, passed by value(in order not to change it outside the function). */
	int findMaxLenOfCellInCols(); /**< Function to fill #lenOfMaxCols */
	/** Function to allign the table to the #maxRow and #maxCol */
	void fillTheEmptyCells(); 
	
public:
	Table();

	/**
	* Getters @see getCellOnRow() @see getRows()
	*/
	int getMaxRow() const;
	const char* getCellOnRow(int row, int col) const; /**< Getter for a cell by its row and col. */
	Row* getRows() const;

	void addRow(int numOfRow); /**< Adding a row in the table by its position(starting from 1) */

	void edit(const String& value, int row, int col); /**<Function used in the CommandLine class to edit value of a cell. */
	/**
	* The main function that calculates the final result(with the necessary validations) of a formula
	* @returns the final result that will be the new value of the specified cell.
	*/
	bool calculateFormulaCellsReference(int row, int col, double& res);
	/**
	* Function used in the CommandLine class to print the content of a table.
	*/
	void print();
};