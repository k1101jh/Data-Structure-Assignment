#include <iostream>
#include "DoublyListP.cpp"
using namespace std;

void PrintList(listClass &LC)				// 리스트를 출력하는 함수 
{
	int item;
	
	for(int i = 1; i <= LC.Length(); i++)
	{
		LC.Retrieve(i, item);
		cout << item << " ";
	}
	cout << endl;
}


int main()
{
	listClass LC;
	
	int input, position;
	while(true)
	{ 
		cout << "Insert : 1, Delete : 2, Retrieve : 3, Copy List : 4, Is Empty? : 5, Length : 6, Exit : 0 >> ";
		cin >> input;
		if(input == 0)
			break;
		switch(input)
		{
			case 1:		// 삽입 
				cout << "Insert Position and Number >> ";
				cin >> position >> input;
				LC.Insert(position, input);
				cout << "List item : ";
				PrintList(LC);
				break;
			case 2: 	// 삭제 
				cout << "Delete Position >> ";
				cin >> position;
				LC.Delete(position);
				cout << "List item : ";
				PrintList(LC);
				break;
			case 3:		// 검색 
				int item;
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
				break;
			case 4:		// 리스트 복사 
				{
					listClass LC2(LC);
					cout << "List1 item : ";
					PrintList(LC);
					cout << "New List item : ";
					PrintList(LC2);
					break;
				}
			case 5:		// 리스트가 비었는지 확인 
				cout << ((LC.IsEmpty()) ? "Empty" : "Not Empty") << endl;
				break;
			case 6:		// 리스트의 길이 
				cout << LC.Length() << endl;
				break;
		}
	}
}


