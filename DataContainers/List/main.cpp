#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
//#define DEBUG

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Iterator;
		friend class ReverseIterator;
	};// *Head, *Tail;
	Element* Head;
	Element* Tail;
	int size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		Iterator& operator++();
		Iterator& operator--();

		const int& operator*()const;
		int& operator*();
		bool operator!=(const Iterator& other)const;

		operator bool()const;
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();

		ReverseIterator& operator++();
		ReverseIterator& operator--();
		const int& operator*()const;
		int& operator*();

		bool operator!=(const ReverseIterator& other)const;
		operator bool()const;
		};



	const Iterator begin()const;
	const Iterator end()const;
	const ReverseIterator rbegin()const;
	const ReverseIterator rend()const;

	List();
	List(const List& other);
	List(const std::initializer_list<int>& il);
	~List();
	//			Operators:
	List& operator=(const List& other);

	//			Adding elements:
	void push_front(int Data);
	void push_back(int Data);

	//			Removing elements:
	void pop_front();
	void pop_back();
	void erase(int index);

	//			Methods:
	void print();
	void print_reverse();
};


//////////////////////////////////////////////////////////////////////////////////			ITERATOR			/////////////////////////////////////////////////////////////////////////////////////////////


List::Iterator::Iterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
List::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
List::Iterator& List::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
List::Iterator& List::Iterator::operator--()
{
	Temp = Temp->pPrev;
	return *this;
}

const int& List::Iterator::operator*()const
{
	return Temp->Data;
}
int& List::Iterator::operator*()
{
	return Temp->Data;
}
bool List::Iterator::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}

List::Iterator::operator bool()const
{
	return Temp;
}


//////////////////////////////////////////////////////////////////////////////////			REVERSE_ITERATOR			//////////////////////////////////////////////////////////////


List::ReverseIterator::ReverseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

}
List::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

}

List::ReverseIterator& List::ReverseIterator::operator++()
{
	Temp = Temp->pPrev;
	return *this;
}
List::ReverseIterator& List::ReverseIterator::operator--()
{
	Temp = Temp->pNext;
	return *this;
}
const int& List::ReverseIterator::operator*()const
{
	return Temp->Data;
}
int& List::ReverseIterator::operator*()
{
	return Temp->Data;
}

bool List::ReverseIterator::operator!=(const ReverseIterator& other)const
{
	return this->Temp != other.Temp;
}
List::ReverseIterator::operator bool()const
{
	return this->Temp;
}


//////////////////////////////////////////////////////////////////////////////////			LIST			//////////////////////////////////////////////////////////////


const List::Iterator List::begin()const
{
	return this->Head;
}
const List::Iterator List::end()const
{
	return nullptr;
}
const List::ReverseIterator List::rbegin()const
{
	return Tail;
}
const List::ReverseIterator List::rend()const
{
	return nullptr;
}

List::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
List::List(const List& other) :List()
{
	//while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "CopyConstuctor:\t" << this << endl;
}
List::List(const std::initializer_list<int>& il) :List()
{
	for (const int* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	cout << "ILConstructor:\t" << this << endl;
}
List::~List()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}
//			Operators:
List& List::operator=(const List& other)
{
	if (this == &other)return *this;
	this->~List();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//			Adding elements:
void List::push_front(int Data)
{
	/*Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
		size++;
		return;
	}
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
	size++;*/

	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Head = Head->pPrev = new Element(Data, Head);
	size++;
	//////////////////////////////////////////////////
}
void List::push_back(int Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);

		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
	}
	size++;
}

//			Removing elements:
void List::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
void List::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}
void List::erase(int index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}
	if (index >= size)
	{
		return;
	}
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}

//			Methods:
void List::print()
{
	//for (Element* Temp = Head; Temp; Temp++/*Temp = Temp->pNext*/)
	for (Iterator it = Head; it; ++it)
		//for (Iterator it = begin(); it != end(); ++it)
	{
		//cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << *it << endl;
	}
	cout << "List size: \t" << size << endl;
}
void List::print_reverse()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "List size: \t" << size << endl;
}



/////////////////////////////////////////////////////////////////////////////////			MAIN			///////////////////////////////////////////////////////////////



//#define BASE_CHECK
//#define COPY_METHODS
#define tab "\t"
void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK n;
	cout << "Input list size: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	//int index;
	//cout << "Type index of deleting element:\t"; cin >> index;
	list.print();
	//list.erase(index);
	//list.print();
#endif // BASE_CHECK
#ifdef COPY_METHODS
	List list2;
	list2 = list;
	list2.print();
#endif // COPY_METHODS

	List list = { 1,2,3,4,5,6 };
	//list.print();
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	//for (List::Iterator it = list.end(); it != list.begin(); --it)
	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
	/*for (int i : list)
	{
		cout << i << endl;
	}
	cout << endl;*/


}