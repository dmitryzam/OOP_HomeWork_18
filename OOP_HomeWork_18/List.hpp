#pragma once
#include<iostream>
#include<exception>			// для throw
#include<initializer_list>	// для добавления нескольких переменных в коллекцию

namespace my_std {
	template <typename ANY>
	class List {
	private:
		struct Item {
			ANY value = ANY();		// ANY() - это конструктор по умолчанию
			Item* next = nullptr;
			Item* prev = nullptr;
			Item(ANY value) : value(value) {}
		};
		Item* first;
		Item* last;
		size_t length;
		void set_defaults();
	public:
		List();
		// Конструктор, который принимает несколько переменных и вносит их в свою коллекцию:
		List(const std::initializer_list<ANY>& inits);	// const std::initializer_list<ANY>& inits - это инициализаторы
		~List();
		// методы:
		void print()const;
		void reverse_print()const;

		void push_back(ANY value);
		void push_front(ANY value);
		void pop_back();
		void pop_front();
		void clear();

		size_t size()const;
		ANY& front();
		const ANY& front()const;
		ANY& back();
		const ANY& back()const;
	};

	template<typename ANY>
	void List<ANY>::set_defaults() {
		first = nullptr;
		last = nullptr;
		length = 0;
	}

	template<typename ANY>
	List<ANY>::List() { set_defaults(); }

	template<typename ANY>
	List<ANY>::List(const std::initializer_list<ANY>& inits) {
		set_defaults();
		for (auto el : inits)
			push_back(el);
	}

	template<typename ANY>
	List<ANY>::~List() { clear(); }

	template<typename ANY>
	void List<ANY>::print() const {
		if (first == nullptr) {
			std::cout << '\n';
			return;
		}
		// создадим свой указатель:
		Item* current = first;	// и направляем его на первый элемент
		do {
			std::cout << current->value << ' ';		// выводим значение текущего указателя
			current = current->next;	// перенаправляем указатель на следующий элемент
		} while (current != nullptr);
		std::cout << std::endl;
	}

	template<typename ANY>
	void List<ANY>::reverse_print() const {
		if (last == nullptr) {
			std::cout << '\n';
			return;
		}
		// создадим свой указатель:
		Item* current = last;	// и направляем его на первый элемент
		do {
			std::cout << current->value << ' ';		// выводим значение текущего указателя
			current = current->prev;	// перенаправляем указатель на следующий элемент
		} while (current != nullptr);
		std::cout << std::endl;
	}

	template<typename ANY>
	void List<ANY>::push_back(ANY value) {
		if (last == nullptr) {
			last = first = new Item(value);
			++length;
			return;
		}
		// взяли поле next и выделели ему новую ячейку памяти:
		last->next = new Item(value);
		// указатель prev должен указывать на текущий элемент:
		last->next->prev = last;
		// указатель last должен указывать на :
		last = last->next;
		++length;
	}

	template<typename ANY>
	void List<ANY>::push_front(ANY value) {
		if (first == nullptr) {
			first = last = new Item(value);
			++length;
			return;
		}
		// берем первый элемент и берем его prev значение и выделяем ему новый элемент и задаем ему значение:
		first->prev = new Item(value);
		//
		first->prev->next = first;
		//
		first = first->prev;
		++length;
	}

	template<typename ANY>
	void List<ANY>::pop_back() {
		if (last == nullptr)
			throw std::exception("List have no elements");
		if (first == last) {	// когда в коллекции один элемент
			delete last;
			set_defaults();
			return;
		}
		last = last->prev;	// перенаправляем last на предпоследний элемент.
		delete last->next;	// удаляем последний элемент
		last->next = nullptr;	// перенаправляем теперь уже последнеого (а был предпоследний) элемента на nullptr
		--length;
	}

	template<typename ANY>
	void List<ANY>::pop_front() {
		if (first == nullptr)
			throw std::exception("List have no elements");
		if (first == last) {	// когда в коллекции один элемент
			delete first;
			set_defaults();
			return;
		}
		first = first->next;	// перенаправляем first на второй элемент.
		delete first->prev;		// удаляем первый элемент
		first->prev = nullptr;	// перенаправляем теперь уже первый (а был второй) элемент на nullptr
		--length;
	}

	template<typename ANY>
	void List<ANY>::clear() {
		if (first == nullptr)
			return;
		Item* current = first;
		do {
			Item* to_delete = current;
			current = current->next;
			delete to_delete;

		} while (current != nullptr);
		set_defaults();
	}

	template<typename ANY>
	size_t List<ANY>::size() const {
		return length;
	}

	template<typename ANY>
	ANY& List<ANY>::front() {
		return first->value;
	}

	template<typename ANY>
	const ANY& List<ANY>::front() const {
		return first->value;
	}

	template<typename ANY>
	ANY& List<ANY>::back() {
		return last->value;
	}

	template<typename ANY>
	const ANY& List<ANY>::back() const {
		return last->value;
	}
}