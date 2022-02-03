#include "genericStackDL.h"
using namespace std;

template <class T>
stackClass<T>::stackClass()
{
	StackList = new listClass<T>();				// ����Ʈ ���� 
}

template <class T>
stackClass<T>::stackClass(const stackClass& S)
{
	StackList = new listClass<T>(*S.StackList);	// ����Ʈ ���� 
}

template <class T>
stackClass<T>::~stackClass()
{
	delete StackList;							// ����Ʈ ���� 
}

template <class T>
void stackClass<T>::Push(T Item)
{
	StackList->Insert(1, Item);					// Item ����		
}

template <class T>
T stackClass<T>::Pop()
{
	if(StackList->IsEmpty())					// ������ ������� 
		cout << "Deletion on Empty Stack" << endl;	// Pop �Ұ��� 
	else
	{
		T item;									// ���� ��Ƴ��� ���� 
		StackList->Retrieve(1, item);			// ������ ���Ҹ� �˻��� ���� ȹ�� 
		StackList->Delete(1);					// ������ ���� ���� 
		return item;							// ������ ������ �� ���� 
	}
}

template <class T>
bool stackClass<T>::IsEmpty()
{
	return (StackList->IsEmpty());
}
