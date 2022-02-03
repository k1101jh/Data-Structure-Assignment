#include <iostream>
#include "treeRecord.h"
using namespace std;

// key�� �˻��ϴ� �Լ� 
Nptr Search(Nptr T, const char *key)
{
	// T�� ������� NULL ��ȯ 
	if(T == NULL)
		return NULL;
	else if(T->Data.Key == key)
		return T;
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		return Search(T->LChild, key);
	else
		return Search(T->RChild, key);
}

// key�� �����ϴ� �Լ� 
Nptr Insert(Nptr T, const char *key)
{
	// T�� ������� �� ��� �߰� 
	if(T == NULL)
	{
		T = new node;
		T->Data.Key = key;
		T->Data.count = 1;
		T->LChild = NULL;
		T->RChild = NULL;
	}
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
	{
		T->LChild = Insert(T->LChild, key);
	} 
	else
	{
		T->RChild = Insert(T->RChild, key);
	}
	return T;
}

// T�� �����ļ��ڸ� ã�Ƽ� ������ ��忡 �ִ� �Լ� 
void SuccessorCopy(Nptr& T, dataType& DelNodeData)
{
	// T�� �����ļ����̸� 
	if(T->LChild == NULL)
	{
		// ������ ����� Key�� T�� Key ����(������ Key ����) 
		DelNodeData.Key = T->Data.Key;
		Nptr Temp = T; 
		T = T->RChild;
		delete Temp;
	}
	// �����ļ��ڸ� �˻� 
	else
		SuccessorCopy(T->LChild, DelNodeData); 
}

// key�� ���� ��带 �����ϴ� �Լ� 
void Delete(Nptr &T, const char *key)
{
	// ������ ���� �������� ���� ��� 
	if(T == NULL)
		cout << "No Record with Such Key" << endl;
	// ������ ������ T�� ���� ū ���
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		Delete(T->LChild, key);
	// ������ ������ T�� ���� ���� ���
	else if(strcmp(T->Data.Key.c_str(), key) < 0)
		Delete(T->RChild, key);
	// ������ ���� ã���� ��� 
	else if(T->Data.Key == key)
	{
		// T�� �ڽ��� ���� ��� 
		if((T->LChild == NULL) && (T->RChild == NULL))
		{
			Nptr Temp = T;
			// T�� ����. 
			T = NULL;
			delete Temp;
		}
		// T�� ������ �ڽĸ� ������ ��� 
		else if(T->LChild == NULL)
		{
			Nptr Temp = T;
			T = T->RChild;
			delete Temp;
		}
		// T�� ���� �ڽĸ� ������ ��� 
		else if(T->RChild == NULL)
		{
			Nptr Temp = T;
			T = T->LChild;
			delete Temp;
		}
		// T�� ���� �ڽ��� ��� ������ ��� 
		else
			SuccessorCopy(T->RChild, T->Data);
	}
}

// key�� Update�ϴ� �Լ� 
void Update(Nptr &T, const char *key)
{
	// T�� ����ٸ� ���ο� ��� �߰� 
	if(T == NULL)
	{
		T = new node;
		T->Data.Key = key;
		T->Data.count = 1;
		T->LChild = NULL;
		T->RChild = NULL;
	}
	// Key�� ã�Ҵٸ� �ش� ����� count���� 
	else if(T->Data.Key == key)
		T->Data.count++;
	// T�� Key���� ���� key���� Ŭ ���
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		Update(T->LChild, key);
	// T�� Key���� ���� key���� ���� ���
	else
		Update(T->RChild, key);

}
