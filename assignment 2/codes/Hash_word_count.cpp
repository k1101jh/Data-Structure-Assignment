#include <iostream>
#include "Hash.cpp"
#define HASH_TABLE_SIZE 100
using namespace std;

// 파일을 입력받아 hash table에 저장하는 함수 
void TokensToHash(ifstream& fin, Hash& hash)
{
	// 기본 크기를 100으로 hash table 생성 
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
		// 파일을 입력받아 hash table에 저장 
		TokensToHash(fin, hash);
		// hash table을 파일로 저장 
		hash.Save(strcat(strtok(argv[1], "."), ".hash"));
	}
	return 0;	
}
