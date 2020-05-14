#include "CommandLine.h"
#pragma warning (disable : 4996)

void CommandLine::enterCommand()
{
	cin >> command;
	cin.ignore();
}

void CommandLine::helperForSaveAndSaveas(String& fileName)
{
	ofstream originalFile; // ofstream, ще записваме промените в оригиналния файл
	ifstream copyFile; // ifstream, ще ги четем от файла- копие на оригиналния

	originalFile.open(fileName.getStr());
	copyFile.open("temp.txt");

	while (copyFile.get(letter))
	{
		helperForReadingFromFile(originalFile);
	}

	originalFile.close();
	copyFile.close();
}
void CommandLine::helperForReadingFromFile(ofstream& readFile)
{
	String buff;

	buff.push_back(letter);

	readFile << buff.getStr();
}
void CommandLine::helperToCreateNewFile()
{
	ofstream newFile(fileName.getStr()); // Създаваме празен файл, както е по условие.
	cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << endl;
	newFile.close();
}

void CommandLine::save(String& originalFileName)
{
	helperForSaveAndSaveas(originalFileName);

	cout << "Successfully saved " << fileName.getStr() << endl;
}

void CommandLine::saveas()
{
	String userChosenFileName; // Създаваме името на файла, в което потребителят иска да запише промените.

	while (true)
	{
		cin.get(letter);

		if (letter == ' ' || letter == '\n')
			break;

		userChosenFileName.push_back(letter);
	}

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
	ifstream originalFile; // Четем от оригиналния файл.
	ofstream copyFile; // Записваме промените в копие, за да не променяме съдържанието на оригиналния
	// докато потребителят не използва командата, предназначена за тази промяна(saveas).

	while (strcmp(command, "exit") != 0)
	{
		enterCommand();

		if (strcmp(command, "open") == 0)
		{
			String tempFileName;

			while (true)
			{
				cin.get(letter);

				if (letter == ' ' || letter == '\n')
					break;

				tempFileName.push_back(letter);
				fileName.setStr(tempFileName.getStr());
			}

			originalFile.open(fileName.getStr());
			copyFile.open("temp.txt");

			if (originalFile.fail())
			{
				helperToCreateNewFile();

				originalFile.open(fileName.getStr());
			}
			else
				cout << "Successfully opened" << " " << fileName.getStr();

			while (originalFile.get(letter)) // Записваме оригиналния файл във файла- копие.
			{
				helperForReadingFromFile(copyFile);
			}

			originalFile.close();
			copyFile.close();

			while (true)
			{
				enterCommand();

				if (strcmp(command, "save") == 0)
				{
					save(fileName);
				}

				else if (strcmp(command, "saveas") == 0)
				{
					saveas();
				}

				else if (strcmp(command, "close") == 0)
				{
					close();
					break;
				}

				else if (strcmp(command, "exit") == 0)
				{
					exit();
					return;
				}

				else if (strcmp(command, "help") == 0)
				{
					help();
				}

				else if (strcmp(command, "edit") == 0)
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
					table.edit(cell.getValue(), row, col);
				}

				else if (strcmp(command, "print") == 0)
				{
					table.print();
				}
			}
		}
	}
}