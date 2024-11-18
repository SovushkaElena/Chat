#pragma once
#include <exception>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class bad_range : public exception
{
public:
	virtual const char* what() const noexcept override;
};
class bad_user : public exception 
{
public:
	const char* what() const noexcept;
};
class bad_choice : public exception 
{
public:
	const char* what() const noexcept;
};
class bad_space : public exception 
{
public:
	const char* what() const noexcept;
};
class empty_string : public exception
{
public:
	const char* what() const noexcept;
};

class User
{
	string login;
	string password;
	string name, surname;
public:
	virtual void showMailbox() = 0;
	User(string _login, string _password, string _name, string _surname);
	string getLogin() const;
	string getPassword() const;
	string getName() const;
	string getSurname() const;
	bool сheckLogin(const string& _login) const;
	bool сheckPassword(const string& _password) const;
};

class Message
{
	string from;
	string text;
public:
	Message(string _text, string _from);
	void show() const;
};

class Beseda
{
	vector<Message> mailBox;
public:
	void showMailbox();
	void takeMessage(Message mess);
};
class Messenger : public User
{
	vector<Message> mailBox;
public:
	Messenger(const string& _login, const string& _password, const string& _name, const string& _surname);
	void takeMessage(const Message& mess);
	void showMailbox();
};
class Admin : public User
{
public:
	Admin(const string& _login, const string& _password, const string& _name, const string& _surname);
	void showMailbox() override; //нужна просто для переопределения, чтоб юзер был абстрактным
	void ShowUsers(const vector<Messenger>& Users);
	void Murder(int i, vector<Messenger>& Users);
};

