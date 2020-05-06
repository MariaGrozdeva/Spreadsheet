#include "Cell.h"

class Row
{
private:
    Cell* cells;
    int capacity;
    int id;

public:
    Row(int id = 0);

    void addCell(String& value, int posOfCell);
    void changeCell(String& value, int posOfCell);

    void print() const;
};