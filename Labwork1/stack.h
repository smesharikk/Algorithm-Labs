#include <iostream>

using namespace std;

template <typename t>
class stack
{
private:
	int top = -1;
	t n[20];

public:

	// операция добавления элемента в стек
	void push(t a)
	{
		if (!is_full())                     // если стек не переполнен
		{
			++top;
			n[top] = a;
		}
		else
		{
			cout << "stack overflow" << endl;// попытка снять элемент с пустого стека
		}
	}


	// операция извлечения элемента из стека
	void pop()
	{
		if (!is_empty())                        //если стек не пустой 
		{
			--top;
		}
		else
		{
			cout << "stack underflow " << endl; // попытка снять элемент с пустого стека
		}
	}


	//операция, которая считывает элемент с вершины стека, но не снимает его оттуда
	t peek()
	{
		if (!is_empty())                         // если стек не пустой 
		{
			return n[top];
		}
		else
		{
			cout << "stack underflow " << endl;  // попытка снять элемент с пустого стека
		}
	}


	// проверка стека на пустоту
	bool is_empty()
	{
		if (top == -1)
			return true;
		else
			return false;
	}


	//проверка стека на переполнение
	bool is_full()
	{
		if (top == 19)
			return true;
		else
			return false;
	}


	//подсчёт числа элементов в стеке
	int size()
	{
		return top + 1;
	}

};
