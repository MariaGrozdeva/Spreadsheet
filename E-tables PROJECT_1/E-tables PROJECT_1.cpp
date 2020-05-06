#include "Table.h"

int main()
{
	Table tableTest;

	String testingStr;
	testingStr.setStr("KLETKA");
	String testingStr1;
	testingStr1.setStr("RED");
	String testingStr2;
	testingStr2.setStr("TABLICA");

	tableTest.addCellinTable(testingStr, 2, 3);
	tableTest.addCellinTable(testingStr1, 3, 4);
	tableTest.addCellinTable(testingStr2, 4, 5);
	tableTest.addCellinTable(testingStr, 5, 6);
	tableTest.edit(testingStr2, 3, 4);

	tableTest.print();
}