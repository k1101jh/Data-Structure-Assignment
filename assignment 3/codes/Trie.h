#include "trieRecord.cpp"

class Trie
{
	public:
		int size;
		Nptr *root;
		
	public:
		void Create();
		int Insert(const char *key, int val);
		Nptr Search(const char *key);
		void Delete(const char *key);
		void Save(const char *filename);
		void Open(const char *filename);
};

