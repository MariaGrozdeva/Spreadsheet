#include "CommandLine.h"
#pragma warning (disable : 4996)

void CommandLine::enterCommand()
{
	cin >> command;
	cin.ignore();
}

void CommandLine::setName(String& sampleName)
{
	while (true)
	{
		cin.get(letter);

		if (letter == ' ' || letter == '\n')
			break;

		sampleName.push_back(letter);
	}
}

void CommandLine::helperForSaveAndSaveas(String& fileName)
{
	ofstream file;
	file.open(fileName.getStr());

	int countOfRows = table.getMaxRow();

	for (int i = 1; i < countOfRows; i++)
	{
		if (!table.getRows()[i].getIsEmpty())
		{
			int countOfCols = table.getRows()[i].getCapacity();

			for (int j = 1; j < countOfCols; j++)
			{
				int len = strlen(table.getCellOnRow(i, j));
				file.write(table.getCellOnRow(i, j), len);

				if (j != countOfCols - 1)
					file.write(",", sizeof(char));
			}
		}
		file.write("\n", sizeof(char));
	}

	file.close();
}
void CommandLine::helperToCreateNewFile()
{
	ofstream newFile(fileName.getStr()); // Създаваме празен файл, както е по условие.
	cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << endl;
	newFile.close();
}
void CommandLine::readTableFromFile(ifstream& file)
{
	file.open(fileName.getStr());

	char ch = 'a';
	int currRow = 1;
	int currCol = 1;

	String emptyValue;
	Cell emptyCell;

	String tempValue;
	Cell tempCell;
	Table tempTable;

	bool isRowEmpty = true;

	while (true)
	{
		file.get(ch);

		if (file.eof())
			break;
		if (ch == '\n')
		{
			if (!isRowEmpty)
			{
				tempCell.setValue(tempValue.getStr());
				tempCell.removeSpaces();
				tempTable.edit(tempCell.getValue(), currRow, currCol);
			}

			currRow++;
			currCol = 1;

			tempValue = emptyValue;
			tempCell = emptyCell;

			isRowEmpty = true;
		}

		else if (ch != ',')
		{
			tempValue.push_back(ch);
			isRowEmpty = false;
		}
		else if (ch == ',')
		{
			tempCell.setValue(tempValue.getStr());
			tempCell.removeSpaces();
			tempTable.edit(tempCell.getValue(), currRow, currCol);

			currCol++;

			tempValue = emptyValue;
			tempCell = emptyCell;
		}
	}
	table = tempTable;
}

void CommandLine::edit()
{
	String tempValue;

	int row;
	cin >> row;
	cin.ignore();

	int col;
	cin >> col;
	cin.ignore();

	while (true)
	{
		cin.get(letter);

		if (letter == '\n')
			break;

		tempValue.push_back(letter);
		value.setStr(tempValue.getStr());
	}

	cell.setValue(value.getStr());

	if (cell.checkIfStringIsValidNumber(tempValue) == -1)
	{
		cout << "Error: row:" << row << ", col:" << col << ", ";
		value.print();
		cout << " is unknown data type." << endl;
	}
	table.edit(cell.getValue(), row, col);
}

void CommandLine::save(String& fileName)
{
	helperForSaveAndSaveas(fileName);

	cout << "Successfully saved " << fileName.getStr() << endl;
}

void CommandLine::saveas()
{
	String userChosenFileName; // Създаваме името на файла, в което потребителят иска да запише промените.

	setName(userChosenFileName);

	helperForSaveAndSaveas(userChosenFileName);

	cout << "Successfully saved another " << userChosenFileName.getStr() << endl;
}

void CommandLine::close() const
{
	cout << "Successfully closed" << " " << fileName.getStr();
}

void CommandLine::exit() const
{
	cout << "Exiting the program..." << endl;
}

void CommandLine::help() const
{
	cout << "The following commands are supported:" << endl;
	cout << "open <file>    opens <file>" << endl;
	cout << "close			closes currently opened file" << endl;
	cout << "save			saves the currently open file" << endl;
	cout << "saveas <file>	saves the currently open file in <file>" << endl;
	cout << "help			prints this information" << endl;
	cout << "exit			exists the program" << endl;
}

void CommandLine::open()
{
	cout << "Write exit to stop the program." << endl;

	String emptyFileName;
	ifstream file;

	while (strcmp(command, "exit") != 0)
	{
		enterCommand();

		if (strcmp(command, "open") == 0)
		{
			setName(fileName);

			file.open(fileName.getStr());

			if (file.fail())
			{
				helperToCreateNewFile();

				file.open(fileName.getStr());
			}
			else
				cout << "Successfully opened " << fileName.getStr() << endl;

			file.close();

			readTableFromFile(file);

			while (true)
			{
				enterCommand();
				if (strcmp(command, "open") == 0)
					cout << "You have to close the file before opening another one." << endl;

				else if (strcmp(command, "save") == 0)
					save(fileName);
				
				else if (strcmp(command, "saveas") == 0)
					saveas();

				else if (strcmp(command, "close") == 0)
				{
					close();
					file.close();

					fileName = emptyFileName;
					break;
				}

				else if (strcmp(command, "exit") == 0)
				{
					exit();
					return;
				}

				else if (strcmp(command, "help") == 0)
					help();

				else if (strcmp(command, "edit") == 0)
					edit();

				else if (strcmp(command, "print") == 0)
					table.print();
			}
		}
	}
}