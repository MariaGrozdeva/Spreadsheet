#include "MainCommand.h"

void MainCommand::open()
{
	ifstream originalFile; // Четем от оригиналния файл.
	ofstream copyFile; // Записваме промените в копие, за да не променяме съдържанието на оригиналния
	// докато потребителят не използва командата, предназначена за тази промяна(saveas).

	while (strcmp(command, "exit") != 0)
	{
		setCommand();

		if (strcmp(command, "open") == 0)
		{
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
				ofstream newFile(fileName.getStr()); // Създаваме празен файл, както е по условие.
				cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << endl;
				newFile.close();

				originalFile.open(fileName.getStr());
			}
			else
				cout << "Successfully opened" << " " << fileName.getStr();

			while (originalFile.get(letter)) // Записваме оригиналния файл във файла- копие.
			{
				String buff;

				buff.push_back(letter);

				copyFile << buff.getStr();
			}

			originalFile.close();
			copyFile.close();

			while (true)
			{
				setCommand();

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

				//else if (strcmp(command, "edit") == 0);

				//else if (strcmp(command, "print") == 0);
			}
		}
	}
}