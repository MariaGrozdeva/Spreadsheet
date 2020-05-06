#include "String.h"
using namespace std;

class Cell
{
private:
	String value;
	int row;
	int col;

public:
	Cell();
	Cell(const char* str, int row, int col);

	void setValue(const char* str);
	void setPos(int row, int col);

	const char* getValue() const;

	void print() const;
};