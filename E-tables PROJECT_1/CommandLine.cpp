#include "CommandLine.h"
#pragma warning (disable : 4996)

void CommandLine::setCommand()
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
		String buff;

		buff.push_back(letter);

		originalFile << buff.getStr();
	}

	originalFile.close();
	copyFile.close();
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