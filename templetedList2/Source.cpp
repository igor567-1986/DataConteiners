#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

template <class T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	 unsigned int size;
 public:
	 List()
	 {
		 Head = Tail = nullptr;
		 size = 0;
		 cout << "LConstructor:\t" << this << endl;
	 }
	 ~List()
	 {
		 while (Tail)pop_back();
		 cout << "LDestructor:\t" << this << endl;
	 }
	 void push_front(T Data)
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
	 void push_back(T Data)
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
	 void insert(int Index, T Data)
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
			 for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		 }
		 Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
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
		 cout << "������ ������: " << Head << endl;
		 for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			 cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		 cout << "����� ������: " << Tail << endl;
		 cout << "���������� ��������� ������: " << size << endl;
	 }
	 void reverse_print()const
	 {
		 cout << "����� ������: " << Tail << endl;
		 for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			 cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		 cout << "������ ������: " << Head << endl;
		 cout << "���������� ��������� ������: " << size << endl;
	 }
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������:"; cin >> n;
	List <int> list;
	for (int i = 0; i < n; i++)	list.push_back(rand() % 100);
	list.print();
	list.reverse_print();
}