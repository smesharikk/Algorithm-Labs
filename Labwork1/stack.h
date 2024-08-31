#include <iostream>

using namespace std;

template <typename t>
class stack
{
private:
	int top = -1;
	t n[20];

public:

	// �������� ���������� �������� � ����
	void push(t a)
	{
		if (!is_full())                     // ���� ���� �� ����������
		{
			++top;
			n[top] = a;
		}
		else
		{
			cout << "stack overflow" << endl;// ������� ����� ������� � ������� �����
		}
	}


	// �������� ���������� �������� �� �����
	void pop()
	{
		if (!is_empty())                        //���� ���� �� ������ 
		{
			--top;
		}
		else
		{
			cout << "stack underflow " << endl; // ������� ����� ������� � ������� �����
		}
	}


	//��������, ������� ��������� ������� � ������� �����, �� �� ������� ��� ������
	t peek()
	{
		if (!is_empty())                         // ���� ���� �� ������ 
		{
			return n[top];
		}
		else
		{
			cout << "stack underflow " << endl;  // ������� ����� ������� � ������� �����
		}
	}


	// �������� ����� �� �������
	bool is_empty()
	{
		if (top == -1)
			return true;
		else
			return false;
	}


	//�������� ����� �� ������������
	bool is_full()
	{
		if (top == 19)
			return true;
		else
			return false;
	}


	//������� ����� ��������� � �����
	int size()
	{
		return top + 1;
	}

};
