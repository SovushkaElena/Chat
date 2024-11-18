#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "Header.h"

using namespace std;

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
                
        }
        throw bad_user();
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

        
        std::getline(std::cin, nam);
        if (nam.find(' ') != string::npos)
            throw bad_space();
        if (nam[0] == '\0')
            throw empty_string();
        std::cout << "Введите фамилию: ";
        string surn;        
        
        std::getline(std::cin, surn);
        if (surn.find(' ') != string::npos)
            throw bad_space();
        if (surn[0] == '\0')
            throw empty_string();
        std::cout << "Введите пароль: ";
        string pass;        
        
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
