#include <iostream>
#include "treeRecord.h"
using namespace std;

// key를 검색하는 함수 
Nptr Search(Nptr T, const char *key)
{
	// T가 비었으면 NULL 반환 
	if(T == NULL)
		return NULL;
	else if(T->Data.Key == key)
		return T;
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		return Search(T->LChild, key);
	else
		return Search(T->RChild, key);
}

// key를 삽입하는 함수 
Nptr Insert(Nptr T, const char *key)
{
	// T가 비었으면 새 노드 추가 
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

// T의 중위후속자를 찾아서 삭제할 노드에 넣는 함수 
void SuccessorCopy(Nptr& T, dataType& DelNodeData)
{
	// T가 중위후속자이면 
	if(T->LChild == NULL)
	{
		// 삭제할 노드의 Key에 T의 Key 대입(원래의 Key 삭제) 
		DelNodeData.Key = T->Data.Key;
		Nptr Temp = T; 
		T = T->RChild;
		delete Temp;
	}
	// 중위후속자를 검색 
	else
		SuccessorCopy(T->LChild, DelNodeData); 
}

// key를 갖는 노드를 제거하는 함수 
void Delete(Nptr &T, const char *key)
{
	// 삭제할 값이 존재하지 않을 경우 
	if(T == NULL)
		cout << "No Record with Such Key" << endl;
	// 삭제할 값보다 T의 값이 큰 경우
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		Delete(T->LChild, key);
	// 삭제할 값보다 T의 값이 작은 경우
	else if(strcmp(T->Data.Key.c_str(), key) < 0)
		Delete(T->RChild, key);
	// 삭제할 값을 찾았을 경우 
	else if(T->Data.Key == key)
	{
		// T의 자식이 없을 경우 
		if((T->LChild == NULL) && (T->RChild == NULL))
		{
			Nptr Temp = T;
			// T를 비운다. 
			T = NULL;
			delete Temp;
		}
		// T의 오른쪽 자식만 존재할 경우 
		else if(T->LChild == NULL)
		{
			Nptr Temp = T;
			T = T->RChild;
			delete Temp;
		}
		// T의 왼쪽 자식만 존재할 경우 
		else if(T->RChild == NULL)
		{
			Nptr Temp = T;
			T = T->LChild;
			delete Temp;
		}
		// T의 양쪽 자식이 모두 존재할 경우 
		else
			SuccessorCopy(T->RChild, T->Data);
	}
}

// key를 Update하는 함수 
void Update(Nptr &T, const char *key)
{
	// T가 비었다면 새로운 노드 추가 
	if(T == NULL)
	{
		T = new node;
		T->Data.Key = key;
		T->Data.count = 1;
		T->LChild = NULL;
		T->RChild = NULL;
	}
	// Key를 찾았다면 해당 노드의 count증가 
	else if(T->Data.Key == key)
		T->Data.count++;
	// T의 Key값이 인자 key보다 클 경우
	else if(strcmp(T->Data.Key.c_str(), key) > 0)
		Update(T->LChild, key);
	// T의 Key값이 인자 key보다 작을 경우
	else
		Update(T->RChild, key);

}
