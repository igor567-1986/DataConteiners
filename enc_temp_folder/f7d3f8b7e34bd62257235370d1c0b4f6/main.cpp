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
	Element* get_pNext()const { return pNext; }
	void set_pNext(Element* pNext) { this->pNext = pNext; }
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
		//delete[]this->pNext;
	}
	friend class ForwardList;
};

unsigned int Element::count = 0; //Статическую переменную можно проиницилизировать
// только за классом

class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	// Голова является точкой входа в список
	unsigned int size;
public:
	Element* get_Head()const { return Head; }
	void set_Head(Element* Head) { this->Head = Head; }
	ForwardList() :Head(nullptr),size(0)
	{
		//Конструктор по умолчанию создает пустой список.
		//Если голова указывает на 0,то и список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()

	{
		cout << "LDestructor:\t" << this << endl;
		for (int i = 0; i < size; i++)
		{
		    this->pop_front();
			size++;
		}
		//	this->Head->~Element();
		
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
		size++;
	}
	void push_back(int Data)
	{
		if(Head ==nullptr)return push_front(Data);
		//1) создаем новый элемент:
		Element* New = new Element(Data);
		//2) Доходим до последнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext)	Temp = Temp->pNext;
		// Теперь Итератор указывает на последний элемент списка,
		// и к нему можно пристыковывать новый элемент.
		//3)
		Temp->pNext = New ;
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
		Element* New = new Element(Data);
		//2) Доходим до нужного элемента в список
		Element* Temp = Head;
		for (int i = 0; i < Index - 1;i++)Temp = Temp->pNext;
		//3)Включаем новый элемент в список
		New->pNext = Temp->pNext;
		Temp->pNext = New; 
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
		Element* Temp = Head;  //Temp- это итератор.
		// Итератор-это указатель,при помощи которого можно получить доступ к элементам структуры данных
		cout << "Head:\t" << Head << endl;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;// Переход на следующий элемент
		}
		cout << "Колличество элементов списка:\t   " << size << endl;
		cout << "Общее колличество элементов списка:" << Element:: count << endl;
	}
	
};
ForwardList operator+( ForwardList& left,  ForwardList& right)
{
	Element* Temp = left.get_Head();
	while (Temp->get_pNext())	Temp = Temp->get_pNext();
	Temp->set_pNext(right.get_Head());
	return left;
}


//#define BASE_CHECK
#define COUNT_CHECK
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

	ForwardList list3 = list1 + list2;
	list3.print();

#endif // COUNT_CHECK
}