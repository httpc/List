#include<iostream>
using namespace std;

#define tab "\t"

//1) Element - ��������� ��������� ��������
//2) ForwardList - �������� �� ����������� ��������� � ������, ����������/��������� ���������, � �.�.

class Element
{
	int Data;	//�������� �������� ��������
	Element* pNext;// ����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		this->Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//			Methods:
	void push_front(int Data)
	{
		Element* New = new Element(Data);	//������� ����� �������, � ��������� � ���� ����������� ��������. 
		//������ ���� ������� ����� ������� � ������:
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}

	void print()
	{
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
		//� ��������� ��������� ������.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//������� �� ��������� �������.
		}
	}
};

void main()
{
	int n;
	cout << "Input list size: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
}