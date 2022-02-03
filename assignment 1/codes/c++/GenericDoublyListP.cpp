#include <iostream>
#include "GenericDoublyListP.h"
using namespace std;

template <class T>
listClass<T>::listClass()							// 리스트 생성 
{
	Count = 0;
	Head = NULL;
}

template <class T>
listClass<T>::listClass(const listClass<T> &L)		// 리스트 복사 
{
	Count = L.Count;
	if(L.Head == NULL)
		Head = NULL;
	else
	{
		Head = new node<T>;
		Head->Data = L.Head->Data;
		node<T>* Temp1 = Head; 
		for(node<T>* Temp2 = L.Head->Next;
		Temp2 != NULL; Temp2 = Temp2->Next)
		{
			Temp1->Next = new node<T>;
			Temp1->Next->Prev = Temp1;
			Temp1 = Temp1->Next;
			Temp1->Data = Temp2->Data;
		}
		Temp1->Next = NULL;
	}	
}

template <class T>
listClass<T>::~listClass()
{
	while(!IsEmpty())								// 모든 노드 제거 
		Delete(1);
}

template <class T>
void listClass<T>::Insert(int Position, T Item)		// 노드 삽입 
{
	if((Position > (Count + 1)) || (Position < 1))
		cout << "Position out of Range" << endl;
	else
	{
		node<T>* p = new node<T>;
		p->Data = Item;
		if(Position == 1)
		{
			p->Next = Head;
			if(Head != NULL)
				Head->Prev = p;
			Head = p;
		}
		else
		{
			node<T>* Temp = Head;
			for(int i = 1; i < (Position - 1); i++)
				Temp = Temp->Next;
			if(Temp->Next != NULL)
			{
				p->Next = Temp->Next;				// p의 Next 설정 
				Temp->Next->Prev = p;				// p를 우측 노드의 Prev로 설정
			}
			else
				p->Next = NULL;
			Temp->Next = p;							// p를 좌측 노드의 Next로 설정 
			p->Prev = Temp;							// p의 Prev 설 정
		}
		Count++;
	}
}

template <class T>
void listClass<T>::Delete(int Position)				// 노드 삭제 
{
	node<T>* p = Head;
	if(IsEmpty())
		cout << "Deletion on Empty List" << endl;
	else if((Position > Count) || (Position < 1))
		cout << "Position out of Range" << endl; 
	else
	{
		if(Position == 1)
		{
			p = Head;
			Head = Head->Next;
		}
		else
		{
			node<T>* Temp = Head;
			for(int i = 1; i < (Position-1); i++)
				Temp = Temp->Next;
			p = Temp->Next;
			if(p->Next != NULL)
			{
				Temp->Next = p->Next;
				p->Next->Prev = Temp;
			}
			else
				Temp->Next = NULL;
		}
		Count--;
		delete (p);
	}	
}

template <class T>
void listClass<T>::Retrieve(int Position, T & item)	// 노드 검색 
{
	if((Position > Count || Position < 1))
		cout << "Position out of Range" << endl;
	else
	{
		if(Position == 1)
		{
			item = Head->Data;
		}
		else
		{
			node<T>* Temp = Head;
			for(int i = 1; i < Position; i++)
				Temp = Temp->Next;
			item = Temp->Data;			
		}
	}
}

template <class T>
bool listClass<T>::IsEmpty()						// 리스트가 비었는지 확인 
{
	return (Count == 0);
}

template <class T>
int listClass<T>::Length()							// 리스트의 길이 반환 
{
	return Count;
}


