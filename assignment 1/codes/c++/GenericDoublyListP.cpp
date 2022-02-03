#include <iostream>
#include "GenericDoublyListP.h"
using namespace std;

template <class T>
listClass<T>::listClass()							// ����Ʈ ���� 
{
	Count = 0;
	Head = NULL;
}

template <class T>
listClass<T>::listClass(const listClass<T> &L)		// ����Ʈ ���� 
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
	while(!IsEmpty())								// ��� ��� ���� 
		Delete(1);
}

template <class T>
void listClass<T>::Insert(int Position, T Item)		// ��� ���� 
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
				p->Next = Temp->Next;				// p�� Next ���� 
				Temp->Next->Prev = p;				// p�� ���� ����� Prev�� ����
			}
			else
				p->Next = NULL;
			Temp->Next = p;							// p�� ���� ����� Next�� ���� 
			p->Prev = Temp;							// p�� Prev �� ��
		}
		Count++;
	}
}

template <class T>
void listClass<T>::Delete(int Position)				// ��� ���� 
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
void listClass<T>::Retrieve(int Position, T & item)	// ��� �˻� 
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
bool listClass<T>::IsEmpty()						// ����Ʈ�� ������� Ȯ�� 
{
	return (Count == 0);
}

template <class T>
int listClass<T>::Length()							// ����Ʈ�� ���� ��ȯ 
{
	return Count;
}


