#include <fstream>
#include "String.h"

using namespace std;

const int MAX_SIZE_OF_COMMAND = 8;
class CommandLine
{
private:
	String fileName;
	char command[MAX_SIZE_OF_COMMAND];
	char letter;

	void helperForSaveAndSaveas(String& diffFileName); // &, за да не създаваме копие на името.
// Тази функция е декларирана в private секцията, защото ще я ползваме само ние, не искаме потребителят да има
// достъп до нея. В зависимост от това дали ще я викаме в save или saveas- методите, ще и подаваме съответно
// originalFileName(записваме промените в оригиналния файл) или userChosenFileName(записваме ги в избран от
// потребителя такъв).
	void helperForReadingFromFile(ofstream& readFile);
	void helperToCreateNewFile();

public:
	void enterCommand();

	void save(String& originalFileName);
	void saveas();
	void close() const;
	void exit() const;
	void help() const;

	void open();

	//void print();
	//void edit();
};