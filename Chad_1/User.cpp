#include "Header.h"
#include <string>

using namespace std;

User::User(string _login, string _password, string _name, string _surname) : login(_login), password(_password), name(_name), surname(_surname) {}
string User::getLogin() const
{
	return login;
}
string User::getPassword() const
{
	return password;
}
string User::getName() const
{
	return name;
}
string User::getSurname() const
{
	return surname;
}
bool User::ñheckLogin(const string& _login) const
{
	return login == _login;
}
bool User::ñheckPassword(const string& _password) const
{
	return password == _password;
}