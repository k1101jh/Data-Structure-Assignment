#include <iostream>
#include "DoublyListP.h"
using namespace std;

listClass::listClass()
{
	Count = 0;								// 크기를 0으로 설정 
	Head = NULL;							// Head포인터를 NULL로 설정 
}

listClass::listClass(const listClass &L)
{
	Count = L.Count;						// 크기 복사 
	if(L.Head == NULL)						// L이 비어있으면 
		Head = NULL;						// 빈 리스트로 생성 
	else
	{
		Head = new node;
		Head->Data = L.Head->Data;			// Head node의 데이터 복사 
		Nptr Temp1 = Head;
		for(Nptr Temp2 = L.Head->Next;		// L의 모든 노드를 탐색 
		Temp2 != NULL; Temp2 = Temp2->Next)
		{
			Temp1->Next = new node;			// 새 노드 생성 
			(Temp1->Next)->Prev = Temp1;	// 새 노드의 Prev 설정 
			Temp1 = Temp1->Next;			// 이전 노드의 Next 설정 
			Temp1->Data = Temp2->Data;		// 이전 노드에 값 대입 
		}
		Temp1->Next = NULL;					// 마지막 노드의 Next는 NULL 
	}	
}

listClass::~listClass()
{
	while(!IsEmpty())						// 리스트가 빌 때까지 
		Delete(1);							// 노드 제거 
}

void listClass::Insert(int Position, int Item)
{
	if((Position > (Count + 1)) || (Position < 1))	// Position 값 검사 
		cout << "Position out of Range" << endl;
	else
	{
		Nptr p = new node;							// 새 노드 생성 
		p->Data = Item;								// 값 대입 
		if(Position == 1)							// Position이 1이면 
		{											// Head포인터를 새 노드를 
			p->Next = Head;							// 가리키도록 설정 
			if(Head != NULL)
				Head->Prev = p;
			Head = p;
		}
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < (Position - 1); i++)	// 새 노드를 넣을 위치 - 1까지 
				Temp = Temp->Next;					// 포인터 이동 
			if(Temp->Next != NULL)					// 마지막 노드가 아니면 
			{
				p->Next = Temp->Next;				// p의 Next 설정 
				Temp->Next->Prev = p;				// p를 우측 노드의 Prev로 설정
			}
			else									// 마지막 노드이면 
				p->Next = NULL;
			Temp->Next = p;							// p를 좌측 노드의 Next로 설정 
			p->Prev = Temp;							// p의 Prev 설 정
		}
		Count++;
	}
}

void listClass::Delete(int Position)
{
	Nptr p = Head;
	if(IsEmpty())									// 리스트가 비었는지 검사 
		cout << "Deletion on Empty List" << endl;
	else if((Position > Count) || (Position < 1))	// Position 값 검사 
		cout << "Position out of Range" << endl; 
	else
	{
		if(Position == 1)							// 맨 처음 값을 삭제하는 경우 
		{
			p = Head;
			Head = Head->Next;						// Head 포인터가 다음 값을 
		}											// 가르키도록 변경 
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < (Position-1); i++)	// 삭제할 노드 위치 -1까지 
				Temp = Temp->Next;					// 포인터 이동 
			p = Temp->Next;
			if(p->Next != NULL)						// 마지막 노드가 아니면 
			{
				Temp->Next = p->Next;				// 이전 노드의 Next 설정 
				p->Next->Prev = Temp;				// 다음 노드의 Prev 설정 
			}
			else									// 마지막 노드일 경우 
				Temp->Next = NULL;					// 이전 노드의 Next는 NULL 
		}
		Count--;									// 리스트 크기 감소 
		delete (p);									// 노드 삭제 
	}	
}

void listClass::Retrieve(int Position, int & item)
{
	if((Position > Count || Position < 1))			// Position 값 검사 
		cout << "Position out of Range" << endl;
	else
	{
		if(Position == 1)							// Head 포인터를 검색하면 
		{
			item = Head->Data;						// 맨 처음 값 반환 
		}
		else
		{
			Nptr Temp = Head;
			for(int i = 1; i < Position; i++)		// 검색한 노드 위치까지 
				Temp = Temp->Next;					// 포인터 이동 
			item = Temp->Data;						// 값 반환 
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


