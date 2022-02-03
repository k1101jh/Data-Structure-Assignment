#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include "BST.cpp"
using namespace std;

// 중위순회로 출력하는 함수 
void InOrderPrint(Nptr T)
{
	if(T != NULL)
	{
		InOrderPrint(T->LChild);
		cout << T->Data.Key << " " << T->Data.count << endl;
		InOrderPrint(T->RChild);
	}
}

// Key입력을 받는 함수 
string GetKey()
{
	string key;
	cout << "Key(string) >> ";
	cin >> key;
	return key;
}

int main(int argc, char* argv[])
{
	Nptr tree = NULL;
	int input = 1;
	string key;
	
	cout << "Insert : 1, Delete : 2, Search : 3, Update : 4, Exit : 0 >> ";
	cin >> input;
	while (input != 0)
	{
		switch(input)
		{
			// Insert
			case 1:
				key = GetKey();
				tree = Insert(tree, key.c_str());
				break;
			// Delete
			case 2:
				key = GetKey();
				Delete(tree, key.c_str());
				break;
			// Search
			case 3:
				key = GetKey();
				{
					Nptr temp = Search(tree, key.c_str());
					if(temp != NULL)
					{
						cout << "result : " << endl;
						cout << "\tKey : " << temp->Data.Key << endl;
						cout << "\tCount : " << temp->Data.count << endl;
					}
					else
						cout << "No Such Node" << endl;
				}
				break;
			// Update
			case 4:
				key = GetKey();
				Update(tree, key.c_str());
				break;
			// 잘못된 입력 
			default:
				cout << "Wrong Input" << endl; 
				break;
		}
		InOrderPrint(tree);
		cout << "Insert : 1, Delete : 2, Search : 3, Update : 4, Exit : 0 >> ";
		cin >> input;
	}
	
	// tree 공간 반환 
	while(tree != NULL)
	{
		Delete(tree, tree->Data.Key.c_str());
	}
	
	return 0;
}
