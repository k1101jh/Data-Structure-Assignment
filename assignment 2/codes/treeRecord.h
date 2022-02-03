#include <string.h>
using namespace std;

typedef struct dataRecord
{
	string Key;
	int count;
} dataType;

typedef struct treeRecord
{
	dataType Data;
	struct treeRecord* LChild;
	struct treeRecord* RChild;
} node;

typedef node* Nptr;
