#include "Header.h"
#include <string>
#include <iostream>

Messenger::Messenger(const string& _login, const string& _password, const string& _name, const string& _surname) : User(_login, _password, _name, _surname) {}
void Messenger::takeMessage(const Message& mess)
{
	mailBox.push_back(mess);
}
void Messenger::showMailbox()
{
    if (mailBox.empty())
    {
        std::cout << "Новых сообщений нет" << endl;
    }
    for (const auto& Mes : mailBox)
    {
        Mes.show();
    }
}