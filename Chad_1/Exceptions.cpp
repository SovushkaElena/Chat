#include "Header.h"
#include <exception>

const char* bad_range::what() const noexcept
{
	return "Выход за пределы вектора";
}
const char* bad_user::what() const noexcept
{
	return "Ошибка, пользователя не существует! ";
}
const char* bad_choice::what() const noexcept
{
	return "Ошибка, введите корректное число! ";
}
const char* bad_space::what() const noexcept
{
	return "Ошибка, в вашей строке есть пробел! ";
}
const char* empty_string::what() const noexcept
{
	return "Ошибка, строка не может быть пустой ";
}