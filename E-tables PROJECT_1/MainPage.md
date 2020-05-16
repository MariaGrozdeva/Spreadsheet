@mainpage Short description and main idea of the project

The project is focused mainly on the work with electronic tables. It allows you to create a table with undetermined number of
rows and columns, in which the cells content can be of diverse types. 

The puprose of the project is to simplify the work of a user giving him the opportunity to make tough calculations 
using the built-in formulas in it. Furthermore, the table is is developed in a way that can prevent you from making
mistakes or wrong calculations such as addition of a string to a number, input of invalid values, division by zero, etc.

###Object- oriented design

It's common knowledge that one of the biggest advantages of *Object-Oriented programming language* is *code reuse* which is
possible due to the *relationship* between classes.
The type of realtionship I've found most appropriate for developing the project is **has-a relationship**. The classes created in
this project are said to be **has-a relationship** because of the following reasons:
- Each *row* in the table is simply a majority of cells, ordered in some way. Also, as mentioned previously,
the length of each row is unlimited. Following these motives, the most accurate solution to create Class Row is to make 
it have data member(dynamically allocated aray) which elements are objects of type Cell.

- Following the same arguments, a *table* is nothing more than а set of rows, ordered in a specific way, as well. So it has 
a data member, dynamically allocated array, composed of objects of type Row.

**Conclusively**, the e-table is ,intuitively, some kind of matrix composed of objects of type Row wcich are themselves composed of 
objects of type Cell.