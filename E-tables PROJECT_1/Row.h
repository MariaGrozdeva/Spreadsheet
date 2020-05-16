#include "Cell.h"

class Row
{
private:
    Cell* cells;
    int capacity;
    int id;
    bool isEmpty;

public:
    Row(int id = 0);

    Cell* getCells() const;

    bool getIsEmpty() const;
    const int getCapacity() const;
    const char* getCellStr(int index) const;
    const double getCellValue(int index) const;
    const String getOriginalValue(int index) const;

    bool isFormula(int index) const;

    void addOrEditCell(const String& value, int posOfCell);

    void printCell(int index) const;
    void print() const;
};