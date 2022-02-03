#include <string.h>
using namespace std;

typedef struct dataRecord
{
	string Key;
	int count;
} dataType;

typedef struct nodeRecord
{
	dataType Data;
	struct nodeRecord* next;
} node;

typedef node* Nptr;
