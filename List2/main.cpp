//#include<iostream>
//using namespace std;
//
//#define tab "\t"
//
//class Element
//{
//	int Data;
//	Element* pPrev;
//	Element* pNext;
//	static unsigned int count;
//public:
//
//	Element( int Data,  Element* pNext = nullptr,Element* pPrev= nullptr):Data(Data), pNext(pNext), pPrev(pPrev)
//	{
//		cout << "EConstructor:\t" << this << endl;
//		count++;
//	}
//	~Element()
//	{
//		cout << "EDestructor:\t" << this << endl;
//		count--;
//	}
//	friend class DolbyLinkedList;
//};
//
//unsigned int Element::count = 0;
//
//class DolbyLinkedList
//{
//	Element* Head;
//	Element* Tail;
//	unsigned int size;
//public:
//	DolbyLinkedList() :Head(nullptr), Tail(nullptr), size(0)
//	{
//		cout << "LConstructor:\t" << this << endl;
//	}
//	~DolbyLinkedList()
//	{
//		cout << "LDestructor:\t" << this << endl;
//		while (Head)
//		{
//			Tail = Head->pNext;
//			delete Head;
//			Head = Tail;
//		}
//	}
//	void push_front(int Data)
//	{
//		Element* New = new Element(Data);
//		if (Head == nullptr)
//		{
//			Head = New;
//			Tail = New;
//		}
//		else
//		{
//			Head->pPrev = New;
//			New->pNext = Head;
//			Head = New;
//		}
//		size++;
//	}
//	void push_back(int Data)
//	{
//		Element* New = new Element(Data);
//		if (Head == nullptr)Head = New;
//		else
//		{
//			Tail->pNext = New;
//			New->pPrev = Tail;
//		}
//		Tail = New;
//		size++;
//	}
//	
//	void print()const
//	{
//	cout << "Head:\t" << Head << endl;
//	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
//		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
//	cout << "________________________________________________" << endl;
//	cout << "Tail:\t" << Tail << endl;
//	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
//		cout << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
//	cout << "Колличество элементов списка:\t   " << size << endl;
//	cout << "Общее колличество элементов списка:" << Element::count << endl;
//    }    
//};
//void main()
//{
//	setlocale(LC_ALL, "");
//	int n;
//	cout << "Введите размер списка:"; cin >> n;
//	DolbyLinkedList list;
//	for (int i=0; i < n; i++)
//	{
//		list.push_front(rand() % 100);
//	}
//	list.print();
//
//}
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"


class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend List operator+(const List& left, const List& right);
		friend class List;
	}*Head, * Tail;
	unsigned int size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp ) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BCItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "BCItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp=nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	
	};
	class ConstReversIterator:public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReversIterator()
		{
#ifdef DEBUG
			cout << "RDestructor:\t" << this << endl;	
#endif // DEBUG
		}
		ConstReversIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReversIterator operator++(int)
		{
			ConstReversIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReversIterator operator--(int)
		{
			ConstReversIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp)
		{
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
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReversIterator :public ConstIterator
	{
	public:
		ReversIterator(Element* Temp = nullptr) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ReversIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)push_back(*it);
	}
	List(const List& other) :List()
	{
			*this = other;
			cout << "CopyConstructor:" << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//				Adding Elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index > size)
		{
			cout << "Eror: Out of range" << endl;
			return;
		}
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index-1; i++)Temp = Temp->pPrev;
		}
	/*	Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data,Temp,Temp->pPrev);
		size++;
	}
	//				Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index > size)
		{
			cout << "Eror: Out of range" << endl;
			return;
		}
		if (Index == 0)return pop_front();
		if (Index == size)return pop_back();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//Element* erased = Temp->pPrev->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		size--;
	}

	//				Methods:
	void print()const
	{
		cout << "Голова списка: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Хвост списка: " << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Хвост списка: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Голова списка: " << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		/*Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		return Temp->pNext;*/
		return nullptr;
	}
    ConstReversIterator rbegin()
	{
		return Tail;
	}
	ConstReversIterator rend()
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	friend List operator+(const List& left, const List& right);
	
};
List operator+(const List& left, const List& right)
{
	List cat = left;
	/*for (List::Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);*/
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		cat.push_back(*it);
		//*it *= 100;
	}
	return cat;
}
void FillRand(List& list)
{
	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		*it = rand();
	}
}

//#define BASE_CHECK
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента:"; cin >> index;
	cout << "Введите значение добавляемого элемента:"; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента:"; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef RANGE_BASE_FOR_ARRAY
	List list = { 3,5,8,13,21 };
	list.print();
	list.reverse_print();

	//List list2 = list;		//CopyConstructor
	List list2;
	list2 = list;			//CopyAssignment
	list2.print();
	list2.reverse_print();
#endif // RANGE_BASE_FOR_ARRAY

#ifdef RANGE_FOR_LIST
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (List::ConstReversIterator rit = list.rbegin(); rit != list.rend(); rit++)
		cout << *rit << tab;
	
#endif // RANGE_FOR_LIST

}

