#include <iostream>
#include "Hash.cpp"
#define HASH_TABLE_SIZE 100
using namespace std;

// ������ �Է¹޾� hash table�� �����ϴ� �Լ� 
void TokensToHash(ifstream& fin, Hash& hash)
{
	// �⺻ ũ�⸦ 100���� hash table ���� 
	hash.Create(HASH_TABLE_SIZE);
	
	for(int i = 0; i < hash.size; i++)
		hash.table[i] = NULL;
	
	char item[20];
	fin >> item;
	while(!fin.eof())
	{
		hash.Update(item);
		fin >> item;
	}
	fin.close();
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	else
	{
		ifstream fin;
		fin.open(argv[1]);
		if(!fin)
		{
			cout << "Can't open file" << endl;
			return 0; 
		}
		Hash hash;
		// ������ �Է¹޾� hash table�� ���� 
		TokensToHash(fin, hash);
		// hash table�� ���Ϸ� ���� 
		hash.Save(strcat(strtok(argv[1], "."), ".hash"));
	}
	return 0;	
}
