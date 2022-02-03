#include "Hash.h"
#include <fstream>

// 해시를 구하는 함수 
int strhashfunc(const char *key)
{
	char *str = (char*)key;
	unsigned int hashval = 0;
	for(hashval = 0; *str; str++)
		hashval = *str + hashval;
	return hashval;
}

// 해시 소멸자 
Hash::~Hash()
{
	for(int i = 0; i < size; i++)
	{
		Nptr temp = table[i];
		if(temp != NULL)
		{
			while(temp->next != NULL)
			{
				Nptr temp2 = temp;
				temp = temp->next;
				delete temp2;
			}
		}
	}
	delete[] table; 
}

// 테이블을 생성하는 함수 
void Hash::Create(int tablesize)
{
	size = tablesize;
	count = 0;
	table = new Nptr[size];
	for(int i = 0; i < size; i++)
		table[i] = NULL;
}

// key를 갖는 노드를 삽입하는 함수 
int Hash::Insert(const char *key)
{
	int hash = strhashfunc(key) % size;
	// 해당 key를 갖는 노드 검색 
	Nptr temp = Search(key);
	// 해당 key를 갖는 노드가 없다면 
	if(temp == NULL)
	{
		temp = table[hash];
		// 동일한 hash가 존재하지 않으면 노드 삽입 
		if(temp == NULL)
		{
			table[hash] = new node;
			table[hash]->Data.Key = key;
			table[hash]->Data.count = 1;
			table[hash]->next = NULL;
		}
		// 동일한 hash가 존재할 경우 해당 Table의 마지막에 삽입 
		else
		{
			while(temp->next != NULL)
				temp = temp->next;
			
			Nptr newNode = new node;
			newNode->Data.Key = key;
			newNode->Data.count = 1;
			newNode->next = NULL;
			temp->next = newNode;
		}
		// hash table이 반절 찼을 경우
		// Rehash 실행 
		count++;
		if(count >= (size / 2))
			Rehash(size * 2);
		return 1;
	}
	else
	{
		return 0;
	}
}

// key를 검색하는 함수 
Nptr Hash::Search(const char *key)
{
	int hash = strhashfunc(key) % size;
	Nptr temp = table[hash];
	while(temp != NULL)
	{
		if(temp->Data.Key == key)
			break;
		temp = temp->next;
	}
	
	return temp;
}

// key를 Update하는 함수 
void Hash::Update(const char *key)
{
	int hash = strhashfunc(key) % size;
	Nptr temp = table[hash];
	
	// 동일한 hash가 존재하지 않으면
	// 새 노드 삽입 
	if(temp == NULL)
	{
		table[hash] = new node;
		table[hash]->Data.Key = key;
		table[hash]->Data.count = 1;
		table[hash]->next = NULL;
		
		count++;
		if(count >= (size / 2))
			Rehash(size * 2);
	}
	// 동일한 hash가 존재할 경우 
	else
	{
		while(temp != NULL)
		{ 
			if(temp->Data.Key == key)
				break;
			temp = temp->next;
		}
		// 해당 key가 존재하지 않을 경우
		// 해당 table의 마지막에 노드 삽입 
		if(!temp)
		{
			temp = table[hash];
			while(temp->next != NULL)
				temp = temp->next;
			
			Nptr newNode = new node;
			newNode->Data.Key = key;
			newNode->Data.count = 1;
			newNode->next = NULL;
			temp->next = newNode;
			
			count++;
			if(count >= (size / 2))
				Rehash(size * 2);
		}
		// 동일한 key가 존재할 경우
		else
		{
			temp->Data.count++;
		}
	}
}

// key를 갖는 노드를 제거하는 함수 
void Hash::Delete(const char *key)
{
	int hash = strhashfunc(key) % size;
	
	Nptr temp = table[hash];
	Nptr prevTemp = temp;
	
	if(temp == NULL)
		cout << "No Record with Such Key" << endl;
		
	while(temp != NULL)
	{
		if(temp->Data.Key == key)
		{
			cout << "key : " << temp->Data.Key;
			cout << "\tcount : "<< temp->Data.count << endl;
			
			// 첫 노드가 아닐 경우 
			if(prevTemp != temp)
			{
				// 삭제할 노드의 다음 노드가 존재할 경우 
				if(temp->next != NULL)
					prevTemp->next = temp->next;
				else
					prevTemp->next = NULL;
			}
			// 첫 노드일 경우 
			else
			{
				// 삭제할 노드의 다음 노드가 존재할 경우 
				if(temp->next != NULL)
					table[hash] = temp->next;
				else
					table[hash] = NULL;
			}
			delete temp;
			count--;
			break;
		}
		prevTemp = temp;
		temp = temp->next;
	}
}

// 해시 테이블을 저장하는 함수 
void Hash::Save(const char *filename)
{
	ofstream fout(filename);
	if (!fout) {
		cout << "Save failed..." << endl;
		return;
	}
	
	// table의 크기를 파일의 첫 줄에 저장 
	fout << size << ": size" << endl;
	
	for(int i = 0; i < size; i++)
	{
		// 테이블의 원소가 존재할 경우 
		if(table[i] != NULL)
		{
			Nptr temp = table[i];
			while(temp != NULL)
			{
				fout << temp->Data.Key << " " << temp->Data.count << endl;
				temp = temp->next;
			}
		}
	}
	fout.close();
	
	cout << "Saved!" << endl;
}

// 해시 테이블을 여는 함수 
void Hash::Open(const char *filename)
{
	ifstream fin;
	fin.open(filename);
	if(!fin)
	{
		cout << "Open failed..." << endl;
		return; 
	}

	char line[25];
	string key;
	int count = 0;
	int hash = 0;
	
	// size 구하기 
	fin.getline(line, 25);
	if(fin.eof()) return;
	
	size = stoi(strtok(line, ":"));
	Create(size);
	
	// Hash Table에 값 넣기 
	while(true)
	{
		fin.getline(line, 25);
		if(fin.eof()) break;
		
		// line이 비어있지 않을 경우 
		if(strcmp(line, "") != 0)
		{
			key = strtok(line, " ");
			count = stoi(strtok(NULL, " "));
			hash = strhashfunc(key.c_str()) % size;
		
			Nptr searchTemp = table[hash];
			if(searchTemp == NULL)
			{
				table[hash] = new node;
				table[hash]->Data.Key = key.c_str();
				table[hash]->Data.count = count;
				table[hash]->next = NULL;
			}
			else
			{
				while(searchTemp->next != NULL)
					searchTemp = searchTemp->next;
					
				Nptr newNode = new node;
				newNode->Data.Key = key.c_str();
				newNode->Data.count = count;
				newNode->next = NULL;
				searchTemp->next = newNode;
			}
		}
	}
}

// Rehash를 수행하는 함수 
void Hash::Rehash(int newtablesize)
{
	Nptr *tempTable = table;
	// 새 테이블 생성 
	Create(newtablesize);
	for(int i = 0; i < (size / 2); i++)
	{
		if(tempTable[i] != NULL)
		{
			Nptr temp = tempTable[i];
			Nptr searchTemp;
			while(temp != NULL)
			{
				// hash를 다시 구함 
				int hash = strhashfunc(temp->Data.Key.c_str()) % size;
				searchTemp = table[hash];
				if(searchTemp == NULL)
				{	// 테이블의 원소가 비었다면
					// 노드 복사 
					table[hash] = new node;
					table[hash]->Data.Key = temp->Data.Key;
					table[hash]->Data.count = temp->Data.count;
					table[hash]->next = NULL;
				}
				else
				{	// 테이블의 원소가 존재하면
					// 해당 원소의 마지막에 노드 복사 
					while(searchTemp->next != NULL)
						searchTemp = searchTemp->next;
						
					Nptr newNode = new node;
					newNode->Data.Key = temp->Data.Key;
					newNode->Data.count = temp->Data.count;
					newNode->next = NULL;
					searchTemp->next = newNode;
				}
				// 원래의 테이블 원소 제거 
				Nptr tempfordelete = temp;
				temp = temp->next;
				delete tempfordelete;
			}
		}
	}
	
	// 원래의 테이블 공간 반환 
	delete [] tempTable;
}
