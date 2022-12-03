#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
class ForwardList;

class Element
{
	int Data;           //значение элемента
	Element* pNext;     // Адрес слудующего элемента
	static unsigned int count; //Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
		//delete[]this->pNext;
	}

	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0; //Статическую переменную можно проиницилизировать
// только за классом

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDetructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const { return Temp->Data; }
	int& operator*() { return Temp->Data; }

};
class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	// Голова является точкой входа в список
	unsigned int size;
public:
	Iterator begin(){return Head;}
	Iterator end() { return nullptr; }
	// Constructors
	ForwardList() :Head(nullptr),size(0)
	{
		//Конструктор по умолчанию создает пустой список.
		//Если голова указывает на 0,то и список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}

	~ForwardList()

	{
		cout << "LDestructor:\t" << this << endl;
		while (Head)pop_front();
		/*for (int i = 0; i < size; i++)
		{
		    this->pop_front();
			size++;
		}*/
		//	this->Head->~Element();
		
	}

	//               Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		revers();
		cout << "CopyAssighment:\t" << this << endl;
		return *this;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}

	}
	ForwardList(const ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
		cout << "MoveConst:\t" << this << endl;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssig:\t" << this << endl;
		return *this;
	}
		//                  Adding Elements:
	void push_front(int Data)
	{
		//1)Создаем новый элумент
		Head = new Element(Data,Head);
		////2)Пристыковываем новый элемент к началу списка
		//New->pNext = Head;
		////3)Переводим голову на новый элемент
		//Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if(Head ==nullptr)return push_front(Data);
		//1) создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до последнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext)	Temp = Temp->pNext;
		// Теперь Итератор указывает на последний элемент списка,
		// и к нему можно пристыковывать новый элемент.
		//3)
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error:Out of range" << endl;
			return;
		}
		//1)Создаем новый элемент
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента в список
		Element* Temp = Head;
		for (int i = 0; i < Index - 1;i++)Temp = Temp->pNext;
		//3)Включаем новый элемент в список
		Temp->pNext =new Element(Data,Temp->pNext);
		size++;
	}

	//      Removing elements
	void pop_front()
	{
		 //1) Сохраняем адрес удаляемого элемента
		Element* erased = Head;
		//2) Исключаем элемент из списка
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента списка
		Element* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		//2) удаляем последний элемент из памяти
		delete Temp->pNext;
		//3)Зануляем указатель на следующий элемент
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index > size)
		{
			cout << "Error:Out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		Element* erased =Temp->pNext ;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
		size--;
	}

		   //   Methods
	void print()const
	{
		//Element* Temp = Head;  //Temp- это итератор.
		// Итератор-это указатель,при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp)
		//{
		//	Temp = Temp->pNext;// Переход на следующий элемент
		//}
		cout << "Head:\t" << Head << endl;
		for(Element* Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Колличество элементов списка:\t   " << size << endl;
		cout << "Общее колличество элементов списка:" << Element:: count << endl;
	}
	void revers()
	{
		/*int n = size - 1;
		int buffer=0;
		Element* Temp;
		for (int i = 0; i < n; i++)
		{
			Temp = Head;
			while (Temp->pNext)	Temp = Temp->pNext;
			insert(i,Temp->Data);
			pop_back();
		}*/
		ForwardList revers;
		while(Head)
		{
			revers.push_front(Head->Data);
			pop_front();
		}
		this->Head = revers.Head;
		this->size = revers.size;
		revers.Head = nullptr;

	}
	
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_BASE_FOR_LIST
//#define PREFORMANCE_CHEK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка:"; cin >> n;
	ForwardList list;
	/*list.push_back(1024);
	list.print();
	list.pop_back();
	list.print();*/
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);

	}
	list.print();
	/*list.push_back(123);
	list.print();*/
	//list.pop_back();
	//list.print();
	int index, value;
	//cout << "Введите индекс добавляемого элемента:"; cin >> index;
	//cout << "Введите значение добавляемого элемента:"; cin >> value;
	//list.insert(index, value);
	//list.print();
	list.erase(2);
	list.print();
#endif // BASE_CHECK
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	list3.revers();
	list3.print();

#endif // COUNT_CHECK

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << "\t";
	cout << endl;
	for (int i : arr) cout << i << "\t";
#endif // RANGE_BASE_FOR_ARRAY
#ifdef RANGE_BASE_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)cout << i << "\t"; 
	cout << endl;
#endif // RANGE_BASE_FOR_LIST
#ifdef PREFORMANCE_CHEK
		int n;
	cout << "Введите размер списка :"; cin >> n;
	ForwardList list;
	cout << "List created, loading data..." << endl;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);

	}
	cout << "Data load complete" << endl;
	ForwardList list2 = list;
	//list.print();
	//list2.print();  
#endif // PREFORMANCE_CHEK

}