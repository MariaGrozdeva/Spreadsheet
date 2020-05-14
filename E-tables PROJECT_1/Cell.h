#include "String.h"
using namespace std;

class Cell
{
private:
	String value;
	int row;
	int col;

	int helperForValidity(const char* str, int len, int i);
	int helperForDotCount(const char* str, int len);

public:
	Cell();
	Cell(const char* str, int row, int col);

	void setValue(const char* str);
	void setPos(int row, int col);

	const char* getValueStr() const;
	const String getValue() const;

	int checkIfStringIsValidNumber(const String& value);
	double convertStrToNum();

	void print() const;
};