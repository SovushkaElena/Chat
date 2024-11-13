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


class message
{
    string from;
    string text;
public:
    message(string _text, string _from) : from(_from), text(_text) {}
    void show()
    {
        cout << "\n" << from << ": " << text << endl;
    }
};

class Beseda
{
    vector<message> mailBox;
public:
    void showMailbox()
    {
        if (mailBox.empty())
        {
            cout << "Новых сообщений нет" << endl;
        }
        for (int i = 0; i < mailBox.size(); i++)
        {
            mailBox[i].show();
        }
    }
    void takeMessage(message mess)
    {
        mailBox.push_back(mess);
    }
};

class messenger : public Beseda //юзер - наследник беседы, а чово бы и нет?) ему, как наследнику, добавляются логин пароль и т.д
{
    string login;
    string password;
    string name, surname;
    vector<message> mailBox;
public:

    messenger(string _login, string _password, string _name, string _surname) : login(_login), password(_password), name(_name), surname(_surname)
    {
        cout << "пользователь " << _name << " " << _surname << " создан" << endl;
    }
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
    void show()
    {
        cout << name << " " << surname << " " << login << " " << endl;
    }
};

class Admin : public messenger
{
public:
    Admin(string a, string b, string c, string d) : messenger(a, b, c, d) {}
    void ShowUsers(vector<messenger>& Users)
    {
        for (int i = 0; i < Users.size(); i++)
        {
            cout << i << " - " << Users[i].getLogin() << " " << Users[i].getName() << " " << Users[i].getSurname() << endl;
        }
    }
    void Murder(int i, vector<messenger>& Users )
    {
        try
        {
            if (i < Users.size())
            {
                Users.erase(Users.begin() + i);
                cout << "Пользователь удален" << endl;
            }
            else
                throw bad_range();
            
        }
        catch (bad_range& br)
        {
            cout << br.what() << endl;
        }
        
    }
};

void UI_Actions(vector<messenger>& Users, Beseda& beseda, int user_ndex) //стоило, наверное, сделать это методом класса пользователя и переопределить в админе с расширенным функционалом, но время поджимает
{
    bool kost2 = true;
    while (kost2) { // цикл для выбора действия "написать сообщение", "просмотр ящика", "выход"
        cout << "1 - написать сообщение\n2 - просмотр ящика\n3 - общий чат\n4 - выход" << endl;
        short choice2;
        cin >> choice2;
        switch (choice2)
        {
        case 1:
        {
            try {
                cout << "Впишите пользователя: ";
                string destLogin;
                cin >> destLogin;

                bool recipient_exists = false; // существует ли получатель

                for (int j = 0; j < Users.size(); j++)
                {
                    if (destLogin == Users[j].getLogin())
                    {
                        recipient_exists = true;
                        cout << "Введите ваше сообщение: ";
                        cin.ignore(); // без этой функции программа работает не корректно
                        string text;
                        getline(cin, text);
                        message* Mes = new message(text, (Users[user_ndex].getName() + " " + Users[user_ndex].getSurname()));
                        Users[j].takeMessage(*Mes);
                        delete Mes;
                        cout << "Сообщение отправлено" << endl;
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
                cout << bu.what() << endl;
            }
            
        }
        case 2:
        {
            Users[user_ndex].showMailbox(); //если ящик пуст - об этом напишет
            break; //чтоб прога не падала
        }
        case 3:
        {
            bool kost3 = true;
            while (kost3)
            {
                cout << "1 - Написать сообщение\n2 - Просмотреть сообщения\n3 - Назад" << endl;
                short choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    cout << "Сообщение: " << endl;
                    cin.ignore(); // без этой функции программа работает не корректно
                    string groupMessage;
                    getline(cin, groupMessage);
                    message* grMess = new message(groupMessage, (Users[user_ndex].getName() + " " + Users[user_ndex].getSurname()));
                    beseda.takeMessage(*grMess);
                    delete grMess;
                    break;
                }
                case 2:
                    beseda.showMailbox();
                    break;
                case 3:
                    kost3 = false;
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
            cout << "Неверный выбор, попробуйте еще раз" << endl;
            break;
        }
    }

}

void UI_SignIn(vector<messenger>& Users, Beseda& beseda, Admin& admin)
{    
    cout << "введите логин: ";
    string log;
    cin >> log;
    bool user_exists = false; // существует ли пользователь
    int user_ndex = -1; // индекс пользователя

    if (log == admin.getLogin())
    {
        cout << "введите пароль: ";
        string pass;
        cin >> pass;
        if (pass == admin.getPassword())
        {
            for (int i = 0; i < Users.size(); i++)
            {
                cout << i << " ";
                Users[i].show();
            }
            cout << "Удалить пользователя под номером: ";
            int mark;
            cin >> mark;
            admin.Murder(mark, Users);
        }

        else
            cout << "Неверный пароль! Попробуйте еще раз:" << endl;
    }

    try {
        for (int i = 0; i < Users.size(); i++)
        {
            if (log == Users[i].getLogin())
            {
                user_exists = true;
                user_ndex = i;
                cout << "введите пароль: ";
                string pass;
                cin >> pass;
                if (pass == Users[i].getPassword())
                {
                    UI_Actions(Users, beseda, user_ndex);
                }
                else {
                    cout << "Неверный пароль! Попробуйте еще раз:" << endl;
                }
                break;
            }

        }
        if (!user_exists) { // если пользователя не существует
            throw bad_user();
        }
    }
    catch (bad_user& bu) {
        cout << bu.what() << endl;
    }
    
    
}

void UI_registration(vector<messenger>& Users)
{
    string log;
    bool unique_log = true;
    while (unique_log) { // если логин занят, то цикл будет работать до тех пор, пока пользователь не введет новый логин
        cout << "Введите логин: ";
        cin >> log;
        unique_log = false;

        if (!Users.empty())
        {
            for (int i = 0; i < Users.size(); i++) // проверка логина на уникальность
            {
                if (log == Users[i].getLogin())
                {
                    cout << "Такой пользователь уже существует, попробуйте еще раз \n";
                    unique_log = true; 
                    break;
                }
            }
        }

    }

    cout << "Введите имя: ";
    string nam;
    cin >> nam;
    cout << "Введите фамилию: ";
    string surn;
    cin >> surn;
    cout << "Введите пароль: ";
    string pass;
    cin >> pass;

    messenger* User = new messenger(log, pass, nam, surn);
    Users.push_back(*User);
    delete User;    
}

void UI()
{
    vector<messenger> Users;
    Admin* admin = new Admin("root", "root", "Administrator", "admin");
    Beseda* beseda = new Beseda();

    int choice;
    bool kost = true;
    while (kost)
    {
        try {
            cout << "1 - войти\n2 - зарегистрироваться" << endl;
            cin >> choice;
            if (choice != 1 && choice != 2) { // проверка на правильность вводимого числа
                throw bad_choice();
            }
            switch (choice) //то, что в блоках потом в функции можно закинуть и расчитстить main
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
            cout << bc.what() << endl;
        }
       
    }
}

int main()
{
    
    setlocale(LC_ALL, "ru");
    UI();    
}
