#include "Hash.h"
#include <fstream>

// �ؽø� ���ϴ� �Լ� 
int strhashfunc(const char *key)
{
	char *str = (char*)key;
	unsigned int hashval = 0;
	for(hashval = 0; *str; str++)
		hashval = *str + hashval;
	return hashval;
}

// �ؽ� �Ҹ��� 
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

// ���̺��� �����ϴ� �Լ� 
void Hash::Create(int tablesize)
{
	size = tablesize;
	count = 0;
	table = new Nptr[size];
	for(int i = 0; i < size; i++)
		table[i] = NULL;
}

// key�� ���� ��带 �����ϴ� �Լ� 
int Hash::Insert(const char *key)
{
	int hash = strhashfunc(key) % size;
	// �ش� key�� ���� ��� �˻� 
	Nptr temp = Search(key);
	// �ش� key�� ���� ��尡 ���ٸ� 
	if(temp == NULL)
	{
		temp = table[hash];
		// ������ hash�� �������� ������ ��� ���� 
		if(temp == NULL)
		{
			table[hash] = new node;
			table[hash]->Data.Key = key;
			table[hash]->Data.count = 1;
			table[hash]->next = NULL;
		}
		// ������ hash�� ������ ��� �ش� Table�� �������� ���� 
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
		// hash table�� ���� á�� ���
		// Rehash ���� 
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

// key�� �˻��ϴ� �Լ� 
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

// key�� Update�ϴ� �Լ� 
void Hash::Update(const char *key)
{
	int hash = strhashfunc(key) % size;
	Nptr temp = table[hash];
	
	// ������ hash�� �������� ������
	// �� ��� ���� 
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
	// ������ hash�� ������ ��� 
	else
	{
		while(temp != NULL)
		{ 
			if(temp->Data.Key == key)
				break;
			temp = temp->next;
		}
		// �ش� key�� �������� ���� ���
		// �ش� table�� �������� ��� ���� 
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
		// ������ key�� ������ ���
		else
		{
			temp->Data.count++;
		}
	}
}

// key�� ���� ��带 �����ϴ� �Լ� 
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
			
			// ù ��尡 �ƴ� ��� 
			if(prevTemp != temp)
			{
				// ������ ����� ���� ��尡 ������ ��� 
				if(temp->next != NULL)
					prevTemp->next = temp->next;
				else
					prevTemp->next = NULL;
			}
			// ù ����� ��� 
			else
			{
				// ������ ����� ���� ��尡 ������ ��� 
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

// �ؽ� ���̺��� �����ϴ� �Լ� 
void Hash::Save(const char *filename)
{
	ofstream fout(filename);
	if (!fout) {
		cout << "Save failed..." << endl;
		return;
	}
	
	// table�� ũ�⸦ ������ ù �ٿ� ���� 
	fout << size << ": size" << endl;
	
	for(int i = 0; i < size; i++)
	{
		// ���̺��� ���Ұ� ������ ��� 
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

// �ؽ� ���̺��� ���� �Լ� 
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
	
	// size ���ϱ� 
	fin.getline(line, 25);
	if(fin.eof()) return;
	
	size = stoi(strtok(line, ":"));
	Create(size);
	
	// Hash Table�� �� �ֱ� 
	while(true)
	{
		fin.getline(line, 25);
		if(fin.eof()) break;
		
		// line�� ������� ���� ��� 
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

// Rehash�� �����ϴ� �Լ� 
void Hash::Rehash(int newtablesize)
{
	Nptr *tempTable = table;
	// �� ���̺� ���� 
	Create(newtablesize);
	for(int i = 0; i < (size / 2); i++)
	{
		if(tempTable[i] != NULL)
		{
			Nptr temp = tempTable[i];
			Nptr searchTemp;
			while(temp != NULL)
			{
				// hash�� �ٽ� ���� 
				int hash = strhashfunc(temp->Data.Key.c_str()) % size;
				searchTemp = table[hash];
				if(searchTemp == NULL)
				{	// ���̺��� ���Ұ� ����ٸ�
					// ��� ���� 
					table[hash] = new node;
					table[hash]->Data.Key = temp->Data.Key;
					table[hash]->Data.count = temp->Data.count;
					table[hash]->next = NULL;
				}
				else
				{	// ���̺��� ���Ұ� �����ϸ�
					// �ش� ������ �������� ��� ���� 
					while(searchTemp->next != NULL)
						searchTemp = searchTemp->next;
						
					Nptr newNode = new node;
					newNode->Data.Key = temp->Data.Key;
					newNode->Data.count = temp->Data.count;
					newNode->next = NULL;
					searchTemp->next = newNode;
				}
				// ������ ���̺� ���� ���� 
				Nptr tempfordelete = temp;
				temp = temp->next;
				delete tempfordelete;
			}
		}
	}
	
	// ������ ���̺� ���� ��ȯ 
	delete [] tempTable;
}
