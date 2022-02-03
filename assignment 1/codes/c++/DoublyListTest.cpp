#include <iostream>
#include "DoublyListP.cpp"
using namespace std;

void PrintList(listClass &LC)				// ����Ʈ�� ����ϴ� �Լ� 
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
			case 1:		// ���� 
				cout << "Insert Position and Number >> ";
				cin >> position >> input;
				LC.Insert(position, input);
				cout << "List item : ";
				PrintList(LC);
				break;
			case 2: 	// ���� 
				cout << "Delete Position >> ";
				cin >> position;
				LC.Delete(position);
				cout << "List item : ";
				PrintList(LC);
				break;
			case 3:		// �˻� 
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
			case 4:		// ����Ʈ ���� 
				{
					listClass LC2(LC);
					cout << "List1 item : ";
					PrintList(LC);
					cout << "New List item : ";
					PrintList(LC2);
					break;
				}
			case 5:		// ����Ʈ�� ������� Ȯ�� 
				cout << ((LC.IsEmpty()) ? "Empty" : "Not Empty") << endl;
				break;
			case 6:		// ����Ʈ�� ���� 
				cout << LC.Length() << endl;
				break;
		}
	}
}


