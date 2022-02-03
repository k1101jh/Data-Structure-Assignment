typedef struct nodeRecord
{
	int Data;
	struct nodeRecord *Prev, *Next;
} node;

typedef node* Nptr;
class listClass
{
	public:
		listClass();
		listClass(const listClass &L);
		~listClass();
		void Insert(int Position, int Item);
		void Delete(int Position);
		void Retrieve(int Position, int & item);
		bool IsEmpty();
		int Length();
	private:
		int Count;
		Nptr Head;
};
