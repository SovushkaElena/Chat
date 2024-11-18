#include "Header.h"
#include <string>
#include <iostream>

void Beseda::showMailbox()
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
void Beseda::takeMessage(Message mess)
{
    mailBox.push_back(mess);
}