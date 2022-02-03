#include "GenericDoublyListP.cpp"

template <class T>
class stackClass
{
	public:
		stackClass();
		stackClass(const stackClass<T>& S);
		~stackClass();
		void Push(T Item);
		T Pop();
		bool IsEmpty();
	private:
		listClass<T> *StackList;
};
