#include <iostream>
#include <vector>

using namespace std;


//class message;

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

class messenger
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
        cout << "\n" << name << "\n" << surname << "\n" << login << "\n" << password;
    }
    void showMailbox()
    {
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



int main()
{
    setlocale(LC_ALL, "ru");
    vector<messenger> Users;  
    int choice;    
    bool kost = true;
    while (kost)
    {
        cout << "\n1 - войти\n2 - зарегистрироваться" << endl;        
        cin >> choice;
        if (choice != 1 && choice != 2){ // проверка на правильность вводимого числа
            cout << "Ошибка, введите корректное число! " << endl;
            continue;
        }
        switch (choice) //то, что в блоках потом в функции можно закинуть и расчитстить main
        {
          
        case 1:
        {
            cout << "введите логин: ";
            string log;
            cin >> log;
            bool user_exists = false; // существует ли пользователь
            int user_ndex = -1; // индекс пользователя

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
                        while (true) { // цикл для выбора действия "написать сообщение", "просмотр ящика", "выход"
                            cout << "\n1 - написать сообщение\n2 - просмотр ящика\n3 - выход" << endl;
                            short choice2;
                            cin >> choice2;
                            switch (choice2)
                            {
                            case 1:
                            {
                                cout << "Впишите пользователя: ";
                                string destLogin;
                                cin >> destLogin;

                                bool recipient_exists = false; // существует ли получатель
                                                              
                                for (int j = 0; j < Users.size(); j++)
                                {
                                    if (destLogin == Users[j].getLogin())
                                    {
                                        recipient_exists = true;
                                        cout << "Ваше сообщение: ";
                                        string text;
                                        cin >> text;
                                        message* Mes = new message(text, (Users[i].getName() + " " + Users[i].getSurname()));
                                        Users[j].takeMessage(*Mes);
                                        delete Mes;
                                        break;
                                    }
                                }
                                if (!recipient_exists) // если получателя не существует или еще не создали
                                {
                                    cout << "Ошибка, пользователя не существует!" << endl; 
                                    continue;
                                }
                                break;
                            }
                            case 2:
                            {
                                Users[user_ndex].showMailbox();
                            }
                            case 3:
                            {
                                return 0;
                            }
                            default:   
                                cout << "Неверный выбор, попробуйте еще раз" << endl;
                                break;
                            }
                        }
                        
                    }
                    else {
                        cout << "Неверный пароль! Попробуйте еще раз:" << endl;
                    }
                    break;
                }
               
            }
            if (!user_exists){ // если пользователя не существует
            cout << "Ошибка, пользователя не существует!" << endl;
            }
            break;
        }
        case 2:
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
                            unique_log = true; //
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
            Users[Users.size()-1].show();
        }
        }
    }
}
