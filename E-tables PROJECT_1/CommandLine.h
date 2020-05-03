#include <fstream>
#include "String.h"

using namespace std;

const int MAX_SIZE_OF_COMMAND = 8;

class CommandLine
{
protected: // Тук използваме protected атрибут за достъп, защото в класа MainCommand, които ще е производен
	// за CommandLine, ще искаме да имаме вътрешен достъп до наследените член- данни на базовия клас.
	String fileName;
	char command[MAX_SIZE_OF_COMMAND];
	char letter;

	void helperForSaveAndSaveas(String& diffFileName); // &, за да не създаваме копие на името.
// Тази функция е декларирана в private секцията, защото ще я ползваме само ние, не искаме потребителят да има
// достъп до нея. В зависимост от това дали ще я викаме в save или saveas- методите, ще и подаваме съответно
// originalFileName(записваме промените в оригиналния файл) или userChosenFileName(записваме ги в избран от
// потребителя такъв).

public:
	void setCommand();

	void save(String& originalFileName);
	void saveas();
	void close() const;
	void exit() const;
	void help() const;

	//void print();
	//void edit();
};