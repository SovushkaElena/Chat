#include "Header.h"
#include <string>
#include <iostream>

Message::Message(string _text, string _from) : from(_from), text(_text) {}
void Message::show() const
{
	std::cout << "\n" << from << ": " << text << endl;
}