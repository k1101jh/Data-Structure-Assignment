#include "genericStackDL.h"
using namespace std;

template <class T>
stackClass<T>::stackClass()
{
	StackList = new listClass<T>();				// 리스트 생성 
}

template <class T>
stackClass<T>::stackClass(const stackClass& S)
{
	StackList = new listClass<T>(*S.StackList);	// 리스트 복사 
}

template <class T>
stackClass<T>::~stackClass()
{
	delete StackList;							// 리스트 제거 
}

template <class T>
void stackClass<T>::Push(T Item)
{
	StackList->Insert(1, Item);					// Item 삽입		
}

template <class T>
T stackClass<T>::Pop()
{
	if(StackList->IsEmpty())					// 스택이 비었으면 
		cout << "Deletion on Empty Stack" << endl;	// Pop 불가능 
	else
	{
		T item;									// 값을 담아놓을 변수 
		StackList->Retrieve(1, item);			// 마지막 원소를 검색을 통해 획득 
		StackList->Delete(1);					// 마지막 원소 제거 
		return item;							// 마지막 원소의 값 리턴 
	}
}

template <class T>
bool stackClass<T>::IsEmpty()
{
	return (StackList->IsEmpty());
}
