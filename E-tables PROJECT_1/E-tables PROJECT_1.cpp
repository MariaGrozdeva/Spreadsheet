#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

void save(String& diffFileName);

int main()
{
	char command[8];

	while (strcmp(command, "exit") != 0)
	{
		fstream originalFile;
		ofstream copyFile;

		String fileName;

		cin >> command;
		cin.ignore();

		if (strcmp(command, "open") == 0)
		{
			char letter{ '0' };

			while (true)
			{
				cin.get(letter);

				if (letter == ' ' || letter == '\n')
					break;

				fileName.push_back(letter);
			}

			originalFile.open(fileName.getStr());
			copyFile.open("temp.txt");

			if (originalFile.fail())
			{
				ofstream newFile(fileName.getStr());
				cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << endl;
				newFile.close();

				originalFile.open(fileName.getStr());
			}
			else
				cout << "Successfully opened" << " " << fileName.getStr();

			while (originalFile.get(letter))
			{
				String buff;

				buff.push_back(letter);

				copyFile << buff.getStr();
			}

			originalFile.close();
			copyFile.close();

			while (true)
			{
				cin >> command;
				cin.ignore();

				if (strcmp(command, "close") == 0)
				{
					cout << "Successfully closed" << " " << fileName.getStr();
					break;
				}

				else if (strcmp(command, "exit") == 0)
				{
					cout << "Exiting the program..." << endl;
					return 0;
				}

				else if (strcmp(command, "help") == 0)
				{
					cout << "The following commands are supported:" << endl;
					cout << "open <file>    opens <file>" << endl;
					cout << "close			closes currently opened file" << endl;
					cout << "save			saves the currently open file" << endl;
					cout << "saveas <file>	saves the currently open file in <file>" << endl;
					cout << "help			prints this information" << endl;
				}

				else if (strcmp(command, "save") == 0)
				{
					save(fileName);

					cout << "Successfully saved " << fileName.getStr() << endl;
				}

				else if (strcmp(command, "saveas") == 0)
				{
					String userChosenFileName;

					while (true)
					{
						cin.get(letter);

						if (letter == ' ' || letter == '\n')
							break;

						userChosenFileName.push_back(letter);
					}

					cout << "Successfully saved another " << userChosenFileName.getStr() << endl;

					ofstream userChosenFile;
					userChosenFile.open(userChosenFileName.getStr());

					userChosenFile.close();
				
					save(userChosenFileName);
				}

				else if (strcmp(command, "edit") == 0);

				else if (strcmp(command, "print") == 0);

			}
		}
	}
}

void save(String& diffFileName)
{
	ofstream originalFile;
	fstream copyFile;

	originalFile.open(diffFileName.getStr());
	copyFile.open("temp.txt");

	char letter{ '0' };

	while (copyFile.get(letter))
	{
		String buff;

		buff.push_back(letter);

		originalFile << buff.getStr();
	}

	originalFile.close();
	copyFile.close();
}