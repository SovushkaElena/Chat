#include <iostream>
#include <vector>
#include <string>

using namespace std;

class bad_range : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Выход за пределы вектора";
    }
};

class bad_user : public exception {
public:
    const char* what() const noexcept
    {
        return "Ошибка, пользователя не существует! ";
    }
};

class bad_choice : public exception {
public:
    const char* what() const noexcept
    {
        return "Ошибка, введите корректное число! ";
    }
};
class bad_space : public exception {
public:
    const char* what() const noexcept
    {
        return "Ошибка, в вашей строке есть пробел! ";
    }
};
class empty_string : public exception
{
public:
    const char* what() const noexcept
    {
        return "Ошибка, строка не может быть пустой ";
    }
};

class User {
protected:
    string login;
    string password;
    string name, surname;
public:
    virtual void showMailbox() = 0;

    User(string _login, string _password, string _name, string _surname) : login(_login), password(_password), name(_name), surname(_surname){}

    string getLogin() const
    {
        return login;
    }
    string getPassword() const
    {
        return password;
    }
    string getName() const
    {
        return name;
    }
    string getSurname() const
    {
        return surname;
    }
    bool сheckLogin(const string& _login) const {
        return login == _login;
    }
    bool сheckPassword(const string& _password) const {
        return password == _password;
    }
};


class Message
{
    string from;
    string text;
public:
    Message(string _text, string _from) : from(_from), text(_text) {}

    void show() const
    {
        std::cout << "\n" << from << ": " << text << endl;
    }
};

class Beseda
{
    vector<Message> mailBox;
public:
    void showMailbox()
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
    void takeMessage(Message mess)
    {
        mailBox.push_back(mess);
    }
};

class Messenger : public User 
{
    vector<Message> mailBox;

public:

    Messenger(const string& _login, const string& _password, const string& _name, const string& _surname) : User (_login, _password, _name, _surname)
    {
        std::cout << "Пользователь " << _name << " " << _surname << " создан" << endl;
    }
  
    void takeMessage(const Message& mess)
    {
        mailBox.push_back(mess);
    }

    void showMailbox()
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
};

class Admin : public User {
public:
    Admin(const string& _login, const string& _password, const string& _name, const string& _surname) : User(_login, _password, _name, _surname){}

    void showMailbox() override {}    

    void ShowUsers(const vector<Messenger>& Users) //показывает всех существующих пользователей
    {
        for (int i = 0; i < Users.size(); i++)
        {
            std::cout << i << " - " << Users[i].getLogin() << " " << Users[i].getName() << " " << Users[i].getSurname() << endl;
        }
    }
    void Murder(int i, vector<Messenger>& Users ) //метод удаления указанного пользователя из вектора
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
};

void UI_Actions(vector<Messenger>& Users, Beseda& beseda, Messenger& current_user) //стоило, наверное, сделать это методом класса пользователя и переопределить в админе с расширенным функционалом, но время поджимает
{
    bool kost2 = true;
    while (kost2) { // цикл для выбора действия "написать сообщение", "просмотр ящика", "выход"
        std::cout << "1 - написать сообщение\n2 - просмотр ящика\n3 - общий чат\n4 - выход" << endl;
        short choice2;
        std::cin >> choice2;
        switch (choice2)
        {
        case 1:
        {
            try {
                std::cout << "Введите логин получателя: ";
                string destLogin;
                std::cin >> destLogin;

                bool recipient_exists = false; // существует ли получатель

                for (auto& user : Users) // перебор вектора
                {
                    if (user.сheckLogin(destLogin))
                    {
                        recipient_exists = true;
                        std::cout << "Введите ваше сообщение: ";
                        std::cin.ignore(); // без этой функции программа работает не корректно
                        string text;
                        std::getline(std::cin, text);
                        Message Mes (text, current_user.getName() + " " + current_user.getSurname());
                        user.takeMessage(Mes);
                        std::cout << "Сообщение отправлено" << endl;
                        break;
                    }
                }
                if (!recipient_exists) // если получателя не существует или еще не создали
                {
                    throw bad_user();
                }
                break;
            }
            catch(bad_user& bu){
                std::cout << bu.what() << endl;
            }
            
        }
        case 2:
        {
            current_user.showMailbox(); //если ящик пуст - об этом напишет
            break; //чтоб прога не падала
        }
        case 3:
        {
            bool kost3 = true;
            while (kost3)
            {
                std::cout << "1 - Написать сообщение\n2 - Просмотреть сообщения\n3 - Назад" << endl;
                short choice;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    std::cout << "Сообщение: " << endl;
                    std::cin.ignore(); // без этой функции программа работает не корректно
                    string groupMessage;
                    std::getline(std::cin, groupMessage);
                    Message grMess (groupMessage, current_user.getName() + " " + current_user.getSurname());
                    beseda.takeMessage(grMess);
                    break;
                }
                case 2:
                {
                    beseda.showMailbox();
                    break;
                }
                case 3: {
                    kost3 = false;
                    break;
                }      
                default:
                    std::cout << "Неверный выбор, попробуйте еще раз" << endl;
                    break;
                }
            }
            break;
        }
        case 4:
        {
            kost2 = false;
            //return 0; кладет прогу, поэтому я делал костыльную булю, потому что свичкейс+цикл странно реагируют на break
            break;
        }
        default:
            std::cout << "Неверный выбор, попробуйте еще раз" << endl;
            break;
        }
    }

}

void UI_SignIn(vector<Messenger>& Users, Beseda& beseda, Admin& admin)
{    
    try
    {
    std::cout << "Введите логин: ";
    string log;
    std::cin >> log;
    
    bool recipient_exists = false; // существует ли пользователь   
    
        if (admin.сheckLogin(log))
        {
            recipient_exists = true;
            std::cout << "Введите пароль: ";
            string pass;
            std::cin >> pass;            

            if (admin.сheckPassword(pass))
            {
                admin.ShowUsers(Users);
                std::cout << "Удалить пользователя под номером: ";
                int mark;
                std::cin >> mark;
                admin.Murder(mark, Users);
            }
            else {
                std::cout << "Неверный пароль! Попробуйте еще раз:" << endl;
            }
            return;
        }
        if (!recipient_exists) // если получателя не существует или еще не создали
        {
            throw bad_user();
        }
        for (auto& user : Users)
        {            
                if (user.сheckLogin(log))
                {
                    std::cout << "Введите пароль: ";
                    std::string pass;
                    std::cin >> pass;
                    if (user.сheckPassword(pass))
                    {
                        UI_Actions(Users, beseda, user);
                    }
                    else {
                        std::cout << "Неверный пароль! Попробуйте еще раз:" << endl;
                    }
                    return;
                }
                else
                    throw bad_user();            
        }
    }
    catch (bad_user& bu) {
        std::cout << bu.what() << endl;
    }    
}

void UI_registration(vector<Messenger>& Users)
{
    string log;
    bool unique_log = true;
    try 
    {
        while (unique_log) { // если логин занят, то цикл будет работать до тех пор, пока пользователь не введет новый логин
            std::cout << "Введите логин: ";
            std::cin.ignore(); 
            std::getline(std::cin, log);
            
            if (log.find(' ') != std::string::npos) //проверка строки на наличие пробелов
                throw bad_space();
            if (log[0] == '\0') //проверка строки на пустоту
                throw empty_string();

            unique_log = false;

            for (const auto& user : Users) // перебор вектора
            {
                if (user.сheckLogin(log))
                {
                    std::cout << "Такой пользователь уже существует, попробуйте еще раз \n";
                    unique_log = true;
                    break;
                }
            }
        }

        std::cout << "Введите имя: ";
        string nam;        

        std::cin.ignore();
        std::getline(std::cin, nam);
        if (nam.find(' ') != string::npos)
            throw bad_space();
        if (nam[0] == '\0')
            throw empty_string();
        std::cout << "Введите фамилию: ";
        string surn;
        
        std::cin.ignore();
        std::getline(std::cin, surn);
        if (surn.find(' ') != string::npos)
            throw bad_space();
        if (surn[0] == '\0')
            throw empty_string();
        std::cout << "Введите пароль: ";
        string pass;
        
        std::cin.ignore();
        std::getline(std::cin, pass);
        if (pass.find(' ') != string::npos)
            throw bad_space();
        if (pass[0] == '\0')
            throw empty_string();

        Users.emplace_back(log, pass, nam, surn);
    }
    catch (bad_space& bs)
    {
        std::cout << bs.what() << endl;
    }
    catch (empty_string& es)
    {
        std::cout << es.what() << endl;
    }
}

void UI()
{
    vector<Messenger> Users;
    Admin* admin = new Admin("root", "root", "Administrator", "admin");
    Beseda* beseda = new Beseda();
        
    bool kost = true;
    while (kost)
    {
        try {
            std::cout << "1 - войти\n2 - зарегистрироваться" << endl;
            int choice;
            std::cin >> choice;
            if (choice != 1 && choice != 2) { // проверка на правильность вводимого числа
                throw bad_choice();
            }
            switch (choice) 
            {

            case 1:
            {
                UI_SignIn(Users, *beseda, *admin);
                break;
            }
            case 2:
            {
                UI_registration(Users);
                break;
            }
            }
        }
        catch (bad_choice& bc) {
            std::cout << bc.what() << endl;
        }
    }
    delete admin;
    delete beseda;
}

int main()
{    
    setlocale(LC_ALL, "ru");
    UI();    

    return 0;
}
