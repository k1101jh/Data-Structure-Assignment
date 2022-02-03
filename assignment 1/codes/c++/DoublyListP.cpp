#include <iostream>
#include "DoublyListP.h"
using namespace std;

listClass::listClass()
{
	Count = 0;								// ũ�⸦ 0���� ���� 
	Head = NULL;							// Head�����͸� NULL�� ���� 
}

listClass::listClass(const listClass &L)
{
	Count = L.Count;						// ũ�� ���� 
	if(L.Head == NULL)						// L�� ��������� 
		Head = NULL;						// �� ����Ʈ�� ���� 
	else
	{
		Head = new node;
		Head->Data = L.Head->Data;			// Head node�� ������ ���� 
		Nptr Temp1 = Head;
		for(Nptr Temp2 = L.Head->Next;		// L�� ��� ��带 Ž�� 
		Temp2 != NULL; Temp2 = Temp2->Next)
		{
			Temp1->Next = new node;			// �� ��� ���� 
			(Temp1->Next)->Prev = Temp1;	// �� ����� Prev ���� 
			Temp1 = Temp1->Next;			// ���� ����� Next ���� 
			Temp1->Data = Temp2->Data;		// ���� ��忡 �� ���� 
		}
		Temp1->Next = NULL;					// ������ ����� Next�� NULL 
	}	
}

listClass::~listClass()
{
	while(!IsEmpty())						// ����Ʈ�� �� ������ 
		Delete(1);							// ��� ���� 
}

void listClass::Insert(int Position, int Item)
{
	if((Position > (Count + 1)) || (Position < 1))	// Position �� �˻� 
		cout << "Position out of Range" << endl;
	else
	{
		Nptr p = new node;							// �� ��� ���� 
		p->Data = Item;								// �� ���� 
		if(Position == 1)							// Position�� 1�̸� 
		{											// Head�����͸� �� ��带 
			p->Next = Head;							// ����Ű���� ���� 
			if(Head != NULL)
				Head->Prev = p;
			Head = p;
		}
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < (Position - 1); i++)	// �� ��带 ���� ��ġ - 1���� 
				Temp = Temp->Next;					// ������ �̵� 
			if(Temp->Next != NULL)					// ������ ��尡 �ƴϸ� 
			{
				p->Next = Temp->Next;				// p�� Next ���� 
				Temp->Next->Prev = p;				// p�� ���� ����� Prev�� ����
			}
			else									// ������ ����̸� 
				p->Next = NULL;
			Temp->Next = p;							// p�� ���� ����� Next�� ���� 
			p->Prev = Temp;							// p�� Prev �� ��
		}
		Count++;
	}
}

void listClass::Delete(int Position)
{
	Nptr p = Head;
	if(IsEmpty())									// ����Ʈ�� ������� �˻� 
		cout << "Deletion on Empty List" << endl;
	else if((Position > Count) || (Position < 1))	// Position �� �˻� 
		cout << "Position out of Range" << endl; 
	else
	{
		if(Position == 1)							// �� ó�� ���� �����ϴ� ��� 
		{
			p = Head;
			Head = Head->Next;						// Head �����Ͱ� ���� ���� 
		}											// ����Ű���� ���� 
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < (Position-1); i++)	// ������ ��� ��ġ -1���� 
				Temp = Temp->Next;					// ������ �̵� 
			p = Temp->Next;
			if(p->Next != NULL)						// ������ ��尡 �ƴϸ� 
			{
				Temp->Next = p->Next;				// ���� ����� Next ���� 
				p->Next->Prev = Temp;				// ���� ����� Prev ���� 
			}
			else									// ������ ����� ��� 
				Temp->Next = NULL;					// ���� ����� Next�� NULL 
		}
		Count--;									// ����Ʈ ũ�� ���� 
		delete (p);									// ��� ���� 
	}	
}

void listClass::Retrieve(int Position, int & item)
{
	if((Position > Count || Position < 1))			// Position �� �˻� 
		cout << "Position out of Range" << endl;
	else
	{
		if(Position == 1)							// Head �����͸� �˻��ϸ� 
		{
			item = Head->Data;						// �� ó�� �� ��ȯ 
		}
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < Position; i++)		// �˻��� ��� ��ġ���� 
				Temp = Temp->Next;					// ������ �̵� 
			item = Temp->Data;						// �� ��ȯ 
		}
	}
}

bool listClass::IsEmpty()
{
	return (Count == 0);
}

int listClass::Length()
{
	return Count;
}


