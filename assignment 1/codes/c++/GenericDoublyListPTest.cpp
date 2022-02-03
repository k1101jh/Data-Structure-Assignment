#include <iostream>
#include <string>
#include "GenericDoublyListP.cpp"
using namespace std;

int ListSelection()						// 리스트 선택창을 출력하는 함수 
{
	int input;
	cout << "int List : 1, double List : 2, string List : 3 >> ";
	cin >> input;
	return input;
}

template <class T>
void Insert(listClass<T> &LC)			// 리스트에 아이템을 삽입하는 함수 
{
	int position;
	T item;
	cout << "Insert Position and item >> ";
	cin >> position >> item;
	LC.Insert(position, item);
	cout << "List item : ";
	PrintList(LC);
}	

template <class T>
void Delete(listClass<T> &LC)			// 리스트의 원소를 제거하는 함수 
{
	int position;
	cout << "Delete Position >> ";
	cin >> position;
	LC.Delete(position);
	cout << "List item : ";
	PrintList(LC);
}

template <class T>
void Retrieve(listClass<T> &LC)			// 리스트의 원소를 검색하는 함수 
{
	int position = 0;
	T item;
	cout << "Retrieve Position >> ";
	cin >> position;
	if((position > LC.Length() || position < 1))
		cout << "Position out of Range" << endl;
	else
	{
		LC.Retrieve(position, item);
		cout << "item : " << item << endl;
		cout << "List item : ";
		PrintList(LC);
	}
}

template <class T>
void PrintList(listClass<T> &LC)		// 리스트를 출력하는 함수 
{
	T item;
	for(int i = 1; i <= LC.Length(); i++)
	{
		LC.Retrieve(i, item);
		cout << item << " ";
	}
	cout << endl;
}

void PrintAllList(listClass<int> &int_list, listClass<double> &double_list, listClass<string> &str_list)
{										// 모든 리스트를 출력하는 함수 
	cout << endl << "Items of IntList : " << endl;
	PrintList(int_list);
	cout << endl << "Items of DoubleList : " << endl;
	PrintList(double_list);
	cout << endl << "Items of StringList : " << endl;
	PrintList(str_list);
}

int main()
{
	listClass<int> int_list;
	listClass<double> double_list;
	listClass<string> str_list;
	
	int input, position;
	while(true)
	{ 
		cout << "Insert : 1, Delete : 2, Retrieve : 3, Copy List : 4, Is Empty? : 5, Length : 6, Exit : 0 >> ";
		cin >> input;
		if(input == 0)
			break;
		switch(input)
		{
			case 1:			// 삽입 
				input = ListSelection();
				switch(input)
				{
					case 1:
						Insert(int_list);
						break;
					case 2:
						Insert(double_list);
						break;
					case 3:
						Insert(str_list);
						break;
				}
				break;
			case 2:			// 삭제 
				input = ListSelection();
				switch(input)
				{
					case 1:
						Delete(int_list);
						break;
					case 2:
						Delete(double_list);
						break;
					case 3:
						Delete(str_list);
						break;
				}
				break;
			case 3:			// 검색 
				input = ListSelection();
				switch(input)
				{
					case 1:
						Retrieve(int_list);
						break;
					case 2:
						Retrieve(double_list);
						break;
					case 3:
						Retrieve(str_list);
						break;
				}
				break;
			case 4:			// 리스트 복사 
				input = ListSelection();
				switch(input)
				{
					case 1:
						{
							listClass<int> int_list2(int_list);
							cout << "New int list : ";
							PrintList(int_list2);
							break;
						}
					case 2:
						{
							listClass<double> double_list2(double_list);
							cout << "New double list : ";
							PrintList(double_list2);
							break;
						}
					case 3:
						{
							listClass<string> str_list2(str_list);
							cout << "New string list : ";
							PrintList(str_list2);
							break;
						}
				}
				break;
			case 5:			// 리스트가 비었는지 확인 
				input = ListSelection();
				switch(input)
				{
					case 1:
						cout << "Is int list empty? : " << ((int_list.IsEmpty()) ? "YES" : "NO") << endl;
						break;
					case 2:
						cout << "Is double list empty? : " << ((double_list.IsEmpty()) ? "YES" : "NO") << endl;
						break;
					case 3:
						cout << "Is string list empty? : " << ((str_list.IsEmpty()) ? "YES" : "NO") << endl;
						break;
				}
				break;
			case 6:			// 리스트 길이 반환 
				input = ListSelection();
				switch(input)
				{
					case 1:
						cout << "int list length : " << int_list.Length() << endl;
						break;
					case 2:
						cout << "double list length : " << double_list.Length() << endl;
						break;
					case 3:
						cout << "string list length : " << str_list.Length() << endl;
						break;
				}
				break;
		}
	}
}

