#include "nodeRecord.h"

class Hash
{
	public:
		int size;
		int count;	// 해시 내의 데이터 개수 
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
