#include <iostream>
#pragma warning (disable : 4996)

/// Almost all data used in the project is of type String (allows usage of undetermined length).
class String
{
private:
	char* str;
	int currentEl;
	int capacity;
	void copyFrom(const String& other);
	void free();
	void resize();

public:
	/**
	* Big 4.
	* @see String(const String& other) @see String& operator=(const String& other) @see ~String()
	*/
	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void push_back(char element);

	void setStr(const char* str);
	const char* getStr() const;

	void print() const;
};