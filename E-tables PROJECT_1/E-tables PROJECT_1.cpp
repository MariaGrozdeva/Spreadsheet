#include "Table.h"

int main()
{
	Table tableTest;

	Cell cell1;
	cell1.setValue("= R2C3 / R2C3");
	Cell cell2;
	cell2.setValue("\"5.5.\"");
	Cell cell3;
	cell3.setValue("\"3\"");
	//Cell cell4;
	//cell4.setValue("= R2C3 / R1C2");

	tableTest.edit(cell1.getValue(), 1, 1);
	tableTest.edit(cell2.getValue(), 1, 2);
	tableTest.edit(cell3.getValue(), 2, 3);
	//tableTest.edit(cell4.getValue(), 1, 1);

	tableTest.print();
}