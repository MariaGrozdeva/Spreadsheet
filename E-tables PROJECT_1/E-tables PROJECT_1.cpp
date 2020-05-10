#include "Table.h"

int main()
{
	Table tableTest;

	Cell cell1;
	cell1.setValue("= R1C2 + R2C3");
	Cell cell2;
	cell2.setValue("\"10.5\"");
	Cell cell3;
	cell3.setValue("\"5\"");

	tableTest.edit(cell1.getValue(), 1, 1);
	tableTest.edit(cell2.getValue(), 1, 2);
	tableTest.edit(cell3.getValue(), 2, 3);
	//tableTest.edit(cell3.getValue(), 1, 1);

	tableTest.print();
}