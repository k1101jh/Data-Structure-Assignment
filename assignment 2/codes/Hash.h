#include "nodeRecord.h"

class Hash
{
	public:
		int size;
		int count;	// �ؽ� ���� ������ ���� 
		Nptr *table;
		
	public:
		~Hash();
		void Create(int tablesize);
		int Insert(const char *key);
		Nptr Search(const char *key);
		void Update(const char *key);
		void Delete(const char *key);
		void Save(const char *filename);
		void Open(const char *filename);
		void Rehash(int newtablesize);
};
