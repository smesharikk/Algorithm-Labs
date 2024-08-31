#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

struct Node
{
	float num;
	char sign;
	Node* left;
	Node* right;
};

//New- создание узла

Node* New(int num, char sign) {
	Node* V;
	V = (Node*)malloc(sizeof(Node));
	V->num = num;
	V->sign = sign;
	V->left = V->right = nullptr;
	return V;//возвращаем указатель
}


//Prior- приоритет операций

int Prior(char symbol) {
	if (symbol == '+' or symbol == '-') {
		return 2;
	}
	else if (symbol == '*' or symbol == '/') {
		return 5;
	}
	else if (symbol >= '0' and symbol <= '9') {
		return 10;
	}
	else {
		return 100;//Чтобы не возникало ошибки
	}
}

Node* MakeTree(int first, int last, char* mass)
{ //БЕЗ СКОБОК
	Node* Tree = New(0, '0'); // создать новую вершину
	int MinPrior = 10, i, k, prt;
	if (first == last) // конечная вершина: число
	{
		Tree->num = mass[first];
		Tree->left = NULL;
		Tree->right = NULL;
		return Tree; // выход
	}
	// ищем последнюю операцию с наименьшим приоритетом
	for (i = first; i < last; i++)
	{
		prt = Prior(mass[i]);
		if (prt <= MinPrior)
		{
			MinPrior = prt;
			k = i;
		}
	}
	Tree->sign = mass[k]; // внутренняя вершина (операция)
	Tree->left = MakeTree(first, k - 1, mass); // рекурсивно строим поддеревья
	Tree->right = MakeTree(k + 1, last, mass);
	return Tree;
}

​//​ CalcTree - функция для подсчёта выражения

