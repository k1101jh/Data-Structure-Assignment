#include <iostream>
#include "Hash.cpp"
using namespace std;

// 해쉬의 원소를 출력하는 함수 
void PrintHash(Hash &hash)
{
	Nptr temp;
	for(int i = 0; i < hash.size; i++)
	{
		temp = hash.table[i];
		while(temp != NULL)
		{
			cout << "hash : " << i;
			cout << "\tkey : " << temp->Data.Key;
			cout << "\tcount : "<< temp->Data.count << "\t" << endl;
			temp = temp->next;
		}
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
	Hash hash;
	hash.Create(100);
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
				if(hash.Insert(key.c_str()) ==0)
					cout << "Key already exists" << endl;
				break;
			// Delete
			case 2:
				key = GetKey();
				hash.Delete(key.c_str());
				break;
			// Search
			case 3:
				key = GetKey();
				{
					Nptr temp = hash.Search(key.c_str());
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
				hash.Update(key.c_str());
				break;
			// 잘못된 입력 
			default:
				cout << "Wrong Input" << endl; 
				break;
		}
		PrintHash(hash);
		cout << "Insert : 1, Delete : 2, Search : 3, Update : 4, Exit : 0 >> ";
		cin >> input;
	}
	
	return 0;
}
