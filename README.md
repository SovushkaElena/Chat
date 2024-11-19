# Chad_1
1)Список участников:
Мамаев Алексей
Журкина Елена

3) Идея решения состояла в том, чтобы существовал массив объектов класса пользователя и класс сообщений, а так же общий почтовый ящик, в который могут написать все. 
У каждого пользователя, помимо имени, логина и т.д. должен быть массив объектов сообщений, как почтовый ящик, хранящий письма.
У каждого письма должен быть текст сообщения и имя отправителя.
Как дополнительный, не обговоренный в ТЗ функционал, решили сделать администратора, который мог бы удалять пользователей.

4) Класс пользователя имеет все задуманные поля, при регистрации конструктором заполняется логин, пароль, имя и фамилия, 
а так же по умолчанию создается пустой почтовый ящик.

Класс сообщений содержит текст, который впишет пользватель и имя отправителя - конкатенированная строка из имени и фамилии, полученные через методы-геттеры, 
а так же метод показа всех сообщений в этом ящике, если он пуст, программа так и напишет.

Класс беседы изначально создался с массивом сообщений и методами получения письма и просмотра своего ящика. Так как весь этот функционал есть и в пользователе, беседа стала родителем класса пользователя.

Пользовательский интерфейс создавался без предварительной задумки, поэтому получился очень громоздким и запутанным. под конец работы пришла идея, как было сделать лучше,
но пришлось бы все перелопатить. Изначально все управление было из функции main, чтобы ее расчистить, были созданы 4 функции: UI, UI_signIn, UI_registration и UI-Actions
UI - зацикленно предлагает пользователю выбор, войти в систему, используя логин и пароль или зарегистрироваться, в зависимости от выбора, вызывается UI_SignIn и UI_registrtion, соответсвтенно
UI_registration запрашивает у нового пользователя данные для регистрации, проверяет логин на совпадения и вызывает конструктор пользователя, если логин уникален.
UI_SignIn запрашивает у пользователя логин и проверяет его наличие в массиве пользователей, при совпадении, запросит и проверит пароль по аналогии с логином.
Далее, после авторизации, вызывается функция UI-Actions, в которой дается выбор: написать кому то личное сообщение, проверить свой почтовый ящик, или написать/проверить сообщения беседы.
Проверка ящика вызовет метод ShowMailBox у текущего пользователя. Аналогично, проверка беседы вызовет тот же метод, но у объекта родительского класса беседы.
Написание сообщение попросит у пользователя логин(можно было сделать и e-mail но это просто лишнее поле), кому написать сообщение. У авторизованного пользователя через геттеры получается его имя и фамилия.
Затем вызывается конструктор класса сообщений и созданный объект записывается в ящик конечного пользователя через метод takeMessage.
Запись в беседу работает аналогично, но вместо конечного пользователя - всегда ящик одной и той же беседы.
Администратор задумывался как пользователь с расширенными возможностями, который изначально существует в системе и его не нужно регистрировать. 
С расширенными возможностями все понятно, он может вывести всех пользователей с их индексом и по индексу удалить, а с обычными возможностями пользователя столкнулись с проблемой: 
его создали, как наследника обычного пользователя, но от того, что пользовательский интерфейс далеко не идеален, при попытке получить имя и фамилию отправителя - программа упала, потому что там все на индексах массива 
пользователей, а в этом массиве админа нет:). Можно было бы сделать еще много условий, чтобы админ мог писать сообщения, но все отталкивается от того, что интерфейс, по хорошему, переделать полностью)

5) Проект разрабатывался постепенно, на каждом этапе мы решали возникающие проблемы.
Сначала мы обсудили план реализации, выбрали необходимые инструменты и решили какую "изюминку" сделаем нашему чату.
Параллельно разбирались, как работает гит и гитхаб, поэтому проект был загружен в репозиторий не с самого начала.

- Алексей создал начальную структуру программы, разработал классы, настроил регистрацию пользователей и добавил геттеры.
- Елена добавила циклы, чтобы не выкидывало из программы и она работала корректно, а также реализовала проверки на различные случаи.
- Алексей создал общий чат для всех пользователей.
- Елена добавила привязку пользователей к уникальному индексу.
- Алексей разработал функционал администратора и оптимизировал главный файл программы (мейн).
- Елена добавила исключения и реализовала функции для обработки ввода (гетлайн).

После проверки и доработки кода были внесены следующие изменения: 
Елена:
Перенесла проверку логина и пароля в класс пользователя с использованием перебора вектора.
Исключила динамическое выделение памяти в функциях UI_Actions и UI_Registration.
Добавила обработку некорректного ввода для общего чата.
Создала общий класс User для устранения дублирования функций в классах Messenger и Admin.
Устранила утечки памяти (вызовы delete для объектов admin и beseda).
Внесла другие мелкие корректировки.
Алексей:
Сделал класс User абстрактным.
Реализовал обработку некорректного ввода при регистрации и авторизации.
Добавил еще несколько обработчиков исключений.
Разделил реализацию на файлы .h и .cpp.
Внес другие мелкие корректировки.
