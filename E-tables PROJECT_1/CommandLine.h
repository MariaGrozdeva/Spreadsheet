#include <fstream>
#include "Table.h"

using namespace std;

const int MAX_SIZE_OF_COMMAND = 8;
class CommandLine
{
private:
	String fileName; /**< Undetermined length of the name of a file. */
	String value;
	Cell cell;
	Table table;

	char command[MAX_SIZE_OF_COMMAND];
	char letter;

	void setName(String& sampleName);  /**< Helper to set the name of a file. */

	/** 
	* The functions mentioned below are helpers for the realisation of the main command open().
	* Consequently, they are private member functions.
	* @see helperToCreateNewFile() @see readTableFromFile()
	*/
	void helperForSaveAndSaveas(String& diffFileName); 
	void helperToCreateNewFile(); /**< If the pointed out file doesn't exist, this function creates new, empty one. */
	/**
	* Extracts the content of a file and creates a "virtual table". The user works on it and depending on
	* whether he wants to save the changes or not, he uses the commands save() / saveas() or close() respectively.
	*/
	void readTableFromFile(ifstream& file);

public:
	void enterCommand();

	void edit();
	void save(String& fileName);
	void saveas();
	void close() const;
	void exit() const;
	void help() const;

	void open();
};