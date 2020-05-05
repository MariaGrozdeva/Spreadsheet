#include "Cell.h"

class Row
{
private:
    Cell* row;
    int capacity;
    int id;

public:
    Row(int id = 0);

    void addCell(String& value, int posOfCell);

    void print() const;
};