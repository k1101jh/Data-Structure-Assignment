#include "genericQueueDL.h"

template <class T>
queueClass<T>::queueClass()				
{
	QueueList = new listClass<T>();					// 리스트 생성 
}
	
template <class T>
queueClass<T>::queueClass(const queueClass& Q)
{
	QueueList = new listClass<T>(*Q.QueueList);		// 리스트 복사 
}
	
template <class T>
queueClass<T>::~queueClass()
{
	delete QueueList;								// 리스트 제거 
}
	
template <class T>
void queueClass<T>::Add(T Item)
{
	QueueList->Insert(QueueList->Length() + 1, Item);	// 큐의 마지막에 원소 삽입 
}

template <class T>
T queueClass<T>::Remove()
{
	T item;
	QueueList->Retrieve(1, item);				//  큐의 시작 원소 검색 
	QueueList->Delete(1);						//  큐의 시작 원소 제거 
	
	return item;
}

template <class T>
bool queueClass<T>::IsEmpty()
{
	return QueueList->IsEmpty();
}
