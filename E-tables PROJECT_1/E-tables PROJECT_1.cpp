#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

int main()
{
	char command[8];

	while (strcmp(command, "exit") != 0)
	{
		fstream originalFile;
		ofstream copyOFile;

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
			copyOFile.open("temp.txt");

			if (originalFile.fail())
			{
				ofstream newFile(fileName.getStr());
				cerr << "Such file doesn't exist. A new empty file with the given name was created for you" << endl;
				newFile.close();

				originalFile.open(fileName.getStr());
			}

			while (!originalFile.eof())
			{
				String buff;

				originalFile.get(letter);
				buff.push_back(letter);

				copyOFile << buff.getStr();
			}

			originalFile.close();

			while (true)
			{
				cin >> command;

				if (strcmp(command, "close") == 0)
				{
					copyOFile.close();
					cout << "Successfully closed" << " " << fileName.getStr();
					break;
				}
			}
		}
	}
}