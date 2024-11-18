#include "Header.h"
#include <exception>

const char* bad_range::what() const noexcept
{
	return "����� �� ������� �������";
}
const char* bad_user::what() const noexcept
{
	return "������, ������������ �� ����������! ";
}
const char* bad_choice::what() const noexcept
{
	return "������, ������� ���������� �����! ";
}
const char* bad_space::what() const noexcept
{
	return "������, � ����� ������ ���� ������! ";
}
const char* empty_string::what() const noexcept
{
	return "������, ������ �� ����� ���� ������ ";
}