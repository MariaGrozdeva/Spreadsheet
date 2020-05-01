#include <iostream>
#pragma warning (disable : 4996)

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
	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void push_back(char element);

	const char* getStr() const;

	void print() const;
};