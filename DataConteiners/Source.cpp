#include<iostream>
using namespace std;

class Element
{
	int Data;           //значение элемента
	Element* pNext;     // Адрес слудующего элемента
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
	Element* Head; //указатель на начальный элемент списка
	// Голова является точкой входа в список
public:
	ForwardList() :Head(nullptr)
	{
		//Конструктор по умолчанию создает пустой список.
		//Если голова указывает на 0,то и список пуст
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//                  Adding Elements:
	void push_front(int Data)
	{
		//1)Создаем новый элумент
		Element* New = new Element(Data);
		//2)Пристыковываем новый элемент к началу списка
		New->pNext = Head;
		//3)Переводим голову на новый элемент
		Head = New;

	}
};
void main()
{
	setlocale(LC_ALL, "");
	
	
}