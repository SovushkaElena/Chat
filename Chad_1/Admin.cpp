#include "Header.h"
#include <string>
#include <iostream>

Admin::Admin(const string& _login, const string& _password, const string& _name, const string& _surname) : User(_login, _password, _name, _surname) {}
void Admin::showMailbox() {}
void Admin::ShowUsers(const vector<Messenger>& Users) //показывает всех существующих пользователей
{
    for (int i = 0; i < Users.size(); i++)
    {
        std::cout << i << " - " << Users[i].getLogin() << " " << Users[i].getName() << " " << Users[i].getSurname() << endl;
    }
}

void Admin::Murder(int i, vector<Messenger>& Users) //метод удаления указанного пользователя из вектора
{
    try
    {
        if (i < Users.size())
        {
            Users.erase(Users.begin() + i);
            std::cout << "Пользователь удален" << endl;
        }
        else
            throw bad_range();

    }
    catch (bad_range& br)
    {
        std::cout << br.what() << endl;
    }
}