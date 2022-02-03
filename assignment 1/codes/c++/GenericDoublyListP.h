template <class T>
struct node
{
	T Data;
	struct node *Prev, *Next;
};

template <class T>
class listClass
{
	public:
		listClass();
		listClass(const listClass<T> &L);
		~listClass();
		void Insert(int Position, T Item);
		void Delete(int Position);
		void Retrieve(int Position, T & item);
		bool IsEmpty();
		int Length();
	private:
		int Count;
		node<T>* Head;
};
