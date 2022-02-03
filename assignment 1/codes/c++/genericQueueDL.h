#include "GenericDoublyListP.cpp"

template <class T>
class queueClass
{
	public:
		queueClass();
		queueClass(const queueClass& Q);
		~queueClass();
		void Add(T Item);
		T Remove();
		bool IsEmpty();
	private:
		listClass<T> *QueueList;
};
