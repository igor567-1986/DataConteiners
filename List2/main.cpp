#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pPrev;
	Element* pNext;
	static unsigned int count;
public:

	Element( int Data,  Element* pNext = nullptr,Element* pPrev= nullptr):Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
		count++;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
		count--;
	}
	friend class DolbyLinkedList;
};

unsigned int Element::count = 0;

class DolbyLinkedList
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	DolbyLinkedList() :Head(nullptr), Tail(nullptr), size(0)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	~DolbyLinkedList()
	{
		cout << "LDestructor:\t" << this << endl;
		while (Head)
		{
			Tail = Head->pNext;
			delete Head;
			Head = Tail;
		}
	}
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr)
		{
			Head = New;
			Tail = New;
		}
		else
		{
			Head->pPrev = New;
			New->pNext = Head;
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr)Head = New;
		else
		{
			Tail->pNext = New;
			New->pPrev = Tail;
		}
		Tail = New;
		size++;
	}
	
	void print()const
	{
	cout << "Head:\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "________________________________________________" << endl;
	cout << "Tail:\t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
	cout << "Колличество элементов списка:\t   " << size << endl;
	cout << "Общее колличество элементов списка:" << Element::count << endl;
    }    
};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка:"; cin >> n;
	DolbyLinkedList list;
	for (int i=0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

}