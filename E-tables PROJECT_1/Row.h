#include "Cell.h"

/// Objects of class Row, along with class Cell, build up the table as a matrix(of rows and cols).
class Row
{
private:
    Cell* cells; /**< Dynamically allocated array of objects of type Cell, undetermined length of each row. */
    int capacity;
    int id; /**< Unique number of each row */
    bool isEmpty; /**< Used when reading a table from a file(if row is empty, putting columns is redundant). */

public:
    Row(int id = 0);

    /** Getters for the different data members. @see bool getIsEmpty() const @see const int getCapacity() 
    * const @see const char* getCellStr(int index) const @see const double getCellValue(int index) const
    * @see const String getOriginalValue(int index) const
    */
    Cell* getCells() const;
     
    bool getIsEmpty() const;
    const int getCapacity() const;
    const char* getCellStr(int index) const; /**< Returns the value of a cell as const char* */
    const double getCellValue(int index) const; /**< Returns the value of a cell converted to a number */
    const String getOriginalValue(int index) const; /**< Returns the value of a cell as object of type String */

    /** Returns true when Cell::checkIfStringIsValidNumber(const String& value)
     * returns 2 (the content of a cell is formula).
     */
    bool isFormula(int index) const;

    /** Adds a cell at a certain position. If the capacity of a row is full, resizes it and the adds the cell.
    */
    void addOrEditCell(const String& value, int posOfCell);

    void printCell(int index) const;
    void print() const;
};