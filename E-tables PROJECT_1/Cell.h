#include "String.h"
using namespace std;

/// Objects of class Cell are the main units building up the table. 
class Cell
{
private:
	String value; /**< Type String because each cell could be initialized with a value which length is undetermined. */
	int row; /**< The number of the row in which the cell is situated. */
	int col; /**< The number of the col in which the cell is situated. */

	/**
	* Private member functions.
	* They are used only in the class to help validate numbers. External access should't be allowed.
	* @see helperForDotCount
	*/
	bool helperForValidity(const char* str, int len, int i); 
	bool helperForDotCount(const char* str, int len);
public:
	/**
	* A default constructor and a constructor with parameters.
	* @see Cell(const char* str, int row, int col)
	*/
	Cell();
	Cell(const char* str, int row, int col);

	/**
	* Setter for the value of the cell.
	*/
	void setValue(const char* str);
	/**
	* Setter for the position of the cell.
	*/
	void setPos(int row, int col);

	/**
	* Getters for the value of the cell as const char* and String respectively.
	* @see getValue() const
	*/
	const char* getValueStr() const;
	const String getValue() const;

	/**
	* Member function used in the CommandLine.
	* When a table is read from a file, the unneccessary spaces should be removed.
	* Nonetheless, when the cell value is string or formula, spaces inside it should't be removed.
	* This may cause outputs such as either string, interpreted differently than expected, or wrong formulas. 
	*/
	void removeSpaces();

	/**
	* Member function to check the type of the content of a given cell.
	* It returns different integers according to outcome.
	* -1(invalid), 0(string which is valid number), 1(valid number), 2(formula)
	*/
	int checkIfStringIsValidNumber(const String& value);
	/**
	* Checks the return value of checkIfStringIsValidNumber(const String& value) 
	* If it is either 0 or 1, converts it to number.
	* Else, returns 0.
	*/
	double convertStrToNum();

	void print() const;
};