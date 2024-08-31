#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

//прототипы функций
string pols(string s);// перевод в польскую запись
int prior(char a);    // возращеет приоритет символов цифра 10, ( 0 , ) 1 , + или - 2, * или / 3
bool correct(string p);// проверяет корректность постановки скобок
float rez(string p);// вычисляет значение выражения в польской записи

int main()
{
	setlocale(LC_ALL, "rus");
	string instr;

	cout << "введите выражение (проверка корректности расстановки скобок): " << endl;
	getline(cin, instr);
	cout << "выражение " << ((correct(instr)) ? "корректно" : "не корректно") << endl << endl;


	//cout << "выражение в польской записи: " << "5 7 + 8 4 / -" << endl;
	//cout << "результат: " << rez("5 7 + 8 4 / -") << endl;
	string polskiy = pols(instr);
	cout << "выражение в польской записи:" << polskiy << endl;
	cout << "результат: " << rez(polskiy) << endl;
}


string pols(string s)
{
	stack<char> stack_2;
	string str;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]))
			str += s[i];
		else
		{
			if (stack_2.is_empty())
			{
				stack_2.push(s[i]);
			}
			else
			{
				if (s[i] == ')')
				{
					while (!stack_2.is_empty())
					{
						char element_spiska = stack_2.peek();
						if (element_spiska == '(')
							stack_2.pop();
						else
						{
							str += element_spiska;
							stack_2.pop();
						}
					}
				}
				else
				{
					if (s[i] == '(')
					{
						continue;
					}
					else
					{
						int value_1 = prior(stack_2.peek());
						int value_2 = prior(s[i]);
						if (value_2 > value_1)
						{
							stack_2.push(s[i]);
						}
						else
						{
							while (!stack_2.is_empty())
							{
								char element_spiska = stack_2.peek();
								if (element_spiska == '(')
									stack_2.pop();
								else
								{
									str += element_spiska;
									stack_2.pop();
								}
							}
						}
					}
				}
			}
		}
	}
	return str;
}

int prior(char a)
{
	if (isdigit(a))
		return 10;
	else if (a == '(')
		return 0;
	else if (a == ')')
		return 1;
	else if (a == '+' or a == '-')
		return 2;
	else if (a == '*' or a == '/')
		return 3;
}
bool correct(string p)
{
	stack<char> stack;

	for (int i = 0; i < p.length(); ++i)
	{
		if (p[i] == '(') //'(' – помещается в стек
		{
			stack.push('(');
		}
		if (p[i] == ')') //')' – с вершины стека извлекается '('
		{
			if (!stack.is_empty()) //проверка на пустоту стека
			{
				stack.pop();
			}
			else
			{
				return false;
			}
		}
	}

	if (stack.is_empty())
		return true;
	else
		return false;
}

float rez(string p)	  //функция вычисления результата в польской записи
{
	float chet = 0;
	stack<float> stack;
	for (int i = 0; i < p.length(); ++i)
	{
		chet = 0;
		if (isdigit(p[i]))
		{
			stack.push(p[i] - '0'); //приём перевода символа в цифру
		}
		else if (p[i] == '+')
		{ // сложение
			float a = stack.peek();
			stack.pop();
			float b = stack.peek();
			stack.pop();
			chet = a + b;
			stack.push(chet);
		}
		else if (p[i] == '-')
		{//вычитание 
			float a = stack.peek();
			stack.pop();
			float b = stack.peek();
			stack.pop();
			chet = b - a;
			stack.push(chet);
		}
		else if (p[i] == '*')
		{ //умножение
			float a = stack.peek();
			stack.pop();
			float b = stack.peek();
			stack.pop();
			chet = b * a;
			stack.push(chet);	
		}
		else if (p[i] == '/')
		{ //деление
			float a = stack.peek();
			stack.pop();
			float b = stack.peek();
			stack.pop();
			chet = b / a;
			stack.push(chet);
		}
	}
	return stack.peek(); //возвращаем посчитанный стек
}
