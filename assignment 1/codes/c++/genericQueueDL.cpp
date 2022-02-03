#include "genericQueueDL.h"

template <class T>
queueClass<T>::queueClass()				
{
	QueueList = new listClass<T>();					// ����Ʈ ���� 
}
	
template <class T>
queueClass<T>::queueClass(const queueClass& Q)
{
	QueueList = new listClass<T>(*Q.QueueList);		// ����Ʈ ���� 
}
	
template <class T>
queueClass<T>::~queueClass()
{
	delete QueueList;								// ����Ʈ ���� 
}
	
template <class T>
void queueClass<T>::Add(T Item)
{
	QueueList->Insert(QueueList->Length() + 1, Item);	// ť�� �������� ���� ���� 
}

template <class T>
T queueClass<T>::Remove()
{
	T item;
	QueueList->Retrieve(1, item);				//  ť�� ���� ���� �˻� 
	QueueList->Delete(1);						//  ť�� ���� ���� ���� 
	
	return item;
}

template <class T>
bool queueClass<T>::IsEmpty()
{
	return QueueList->IsEmpty();
}
