#include<iostream>
using namespace std;

#define tab "\t"
//1) Element - описывает структуру элемента
//2) ForwardList - отвечает за объединение элементов в список, добавление/удавление элементов, и т.д.

class Element
{
	int Data;	//Содержит значение элемента
	Element* pNext;// Адрес следующего элемента
	static int count;	//Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;

#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	int& operator*()
	{
		return Temp->Data;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	bool operator!=(Element* other_el)const
	{
		return this->Temp != other_el;
	}

	operator bool()const
	{
		return Temp;
	}
};


class ForwardList
{
	Element* Head;
	int size;
public:

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	int get_size()const
	{
		return this->size;
	}
	ForwardList()
	{
		this->Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		this->Head = nullptr;
		this->size = 0;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(int size):ForwardList()
	{
		while (size--)push_front(0);
	}
	ForwardList(const std::initializer_list<int>& il)
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head != nullptr)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//Operators
	int& operator[](int index)
	{
		if (index >= this->size)throw std::exception("Error: Out of range");
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Добавление элементов
	void push_front(int Data)
	{
		/*
		Element* New = new Element(Data);	//Создаем новый элемент, и сохраняем в него добавляемое значение. 
		//Теперь этот элемент нужно ключить в список:
		New->pNext = Head;
		Head = New;*/

		Head = new Element(Data, Head);

		size++;
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
		size++;
	}
	void insert(int index, int data)
	{
		if (index > size)return;
		if (index == 0)
		{
			push_front(data);
			return;
		}
		Element* New = new Element(data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void erase(int index)
	{
		if (index > size)return;
		if (index == 0)return;
		Element* Temp = Head;
		Element* Temp2 = Head;
		for (int i = 0; i < index - 2; i++)
			Temp = Temp->pNext;
		for (int i = 0; i < index - 1; i++)
			Temp2 = Temp2->pNext;
		Temp->pNext = Temp2->pNext;
		size--;
	}
	//			Удаление элементов:
	void pop_front()
	{
		Element* to_del = Head;	//1) запоминаем адрес удаляемого элемента
		Head = Head->pNext;	//2) исключаем элемент из списка
		delete to_del;	//3) удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	//			Methods:
	void print()
	{
#ifdef OLD_STYLE
		Element* Temp = Head;	//Temp - это итератор.
//Итератор - это указатель, при помощи которого можно получить доступ 
//к элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент.
		}
#endif // OLD_STYLE
		//Temp = Temp->pNext
		//for (Iterator Temp = Head; Temp != nullptr; ++Temp)
		for (Iterator Temp = begin(); Temp != end(); Temp++)
		{
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			cout << *Temp << endl;
		}
		cout << "List size: " << size << endl;
	}
};

#define delimiter "\n----------------------------------\n"

//#define BASE_CHECK
#define PREFORMANCE_CHECK
//#define ITERATORS_CHECK

void main()
{
	int n;
	cout << "Input list size: "; cin >> n;

#ifdef BASE_CHECK
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.push_back(123);
	list.print();
	cout << delimiter;


	/*list.pop_front();
	list.pop_back();
	list.print();
	int index;
	int value;
	cout << "Input index: "; cin >> index;
	cout << "Input value: "; cin >> value;
	list.insert(index, value);
	list.print();*/
#endif // BASE_CHECK

#ifdef PREFORMANCE_CHECK
	ForwardList list(n);

	
		/*for (int i = 0; i < list.get_size(); i++)
		{
			list[i] = rand() % 100;
		}*/
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		*it = rand() % 100;
	}
		cout << "List loaded" << endl;
		//for (int i = 0; i < list.get_size(); i++)
		//{
		//	//cout << list[i] << '\t';
		//	list[i];
		//}
		for (int i : list)
		{
			i;
		}
		cout << endl;
		cout << "List printed" << endl;
	
#endif // PREFORMANCE_CHECK

#ifdef ITERATOERS_CHECK
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i : arr)
	{
		cout << i << endl;
	}



	ForwardList list = { 3, 4, 6, 71, 65 };
	list.print();
	for (int i : list)
	{
		cout << i << endl;
	}
	cout << endl;
#endif // ITERATOERS_CHECK

}