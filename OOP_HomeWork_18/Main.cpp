#include<iostream>
#include"List.hpp"

// Домашняя работа на тему "ПРОСТРАНСТВО ИМЕН".

int main() {

	// Доступ к пространству имен через оператор разрешения области видимости (::)
	my_std::List<int> list1;
	list1.push_back(15);
	list1.push_back(7);
	list1.push_front(42);
	//list1.clear();
	list1.print();
	//list1.reverse_print();
	//list1.pop_back();
	list1.pop_front();
	list1.print();

	// Использование "using-объявление" (в блоке):
	{
		using namespace my_std;
		List<std::string> list2{ "Hello", "World", "Oranges", "Apples" };
		list2.print();
		list2.pop_back();
		list2.print();
	}

	// Ошибка!
	//List<std::string> list2{ "Hello", "World", "Oranges", "Apples" };
	//list2.print();

	return 0;
}